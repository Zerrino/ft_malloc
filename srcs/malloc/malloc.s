bits 64
default rel

%include "includes/malloc.inc"

section .bss
	global	g_global
	g_global: resq 1

section .data

	msg: db 'bonjour', 0
	msg2: db 'test', 0
	msg3: db 'coucou', 0

section .text
		global	ft_malloc

; void	*(*ft_malloc)(size_t size)
;	rdi


ft_malloc:

	xor		rax, rax
	test	rdi, rdi
	jz		.end
	; --- TO-DO ---
	cmp		rdi, SMALL_SIZE
	jbe		.small_malloc
	; CHECKER SI SUPERIEUR A SMALL BLOCK

	add		rdi, 0xfff
	and		rdi, -0x1000
	mov		rcx, rdi
	mov		rsi, rcx
	jmp		.allocate_zone_big
	; --- ALIGNEMENT ---
	;mov		rax, rdi
	;dec		rax
	;bsr		rcx, rdi
	;test	rax, rdi
	;setnz	dil
	;movzx	rdi, dil
	;inc		rdi
	;shl		rdi, cl
	; --- ALIGNE --- CL STILL NUMBER
.small_malloc:
	add		rdi, 15
	and		rdi, -16


	; --- RCX = 16384 ou RCX = 1024 ---
	mov		rcx, rdi
	shr		rcx, 11
	test	rcx, rcx
	setnz	cl
	lea		rcx, [rcx + rcx*4]
	lea		rcx, [rcx + rcx*2]
	inc		rcx
	shl		rcx, 10
	; --- RCX = 16384 ou RCX = 1024 ---


	lea		rax, [rel g_global]
	mov		rax, [rax]
	test	rax, rax
	jne		.not_empty

.allocate_zone:

	mov		rsi, rcx
	shl		rsi, 7

.allocate_zone_big:

	push	rdi
	push	rcx

	mov		rax, SYS_mmap
	mov		rdi, 0
	mov		rdx, PROT_READ | PROT_WRITE
	mov		r10, MAP_PRIVATE | MAP_ANONYMOUS
	mov		r8, -1
	mov		r9, 0
	syscall
	pop		rcx	; size zone/block
	pop		rdi	; size actual block

	cmp		rax, -1
	je		.end





	lea		rsi, [rel g_global] ; addresse de global

	mov		rdx, [rsi]
	test	rdx, rdx
	jne		.g_global_exit

	mov		[rsi], rax ; je met son addresse
	mov		rsi, [rsi]
	cmp		rdi, SMALL_SIZE
	ja		.continue
	or		qword [rsi + t_zone.flag], 1

	jmp		.continue
.g_global_exit:



	mov		rsi, [rsi]
	mov		rdx, [rsi + t_zone.next]



	test	rdx, rdx
	je		.allocate_next
	add		rsi, t_zone.next

	jmp		.g_global_exit

.allocate_next:



	mov		qword [rsi + t_zone.next], rax
	mov		rsi, [rsi + t_zone.next]

.continue:


	mov		qword [rsi + t_zone.size], rcx
	mov		qword [rsi + t_zone.next], 0

	cmp		rdi, SMALL_SIZE
	ja		.end_big

	mov		rax, rcx
	shl		rax, 7
	add		rax, rsi
	mov		qword [rsi + t_zone.numb], rax




.not_empty:

	lea		rsi, [rel g_global]
	mov		rsi, [rsi]


.loop_find_zone:


	mov		rax, [rsi + t_zone.flag]
	and		rax, 2
	jne		.skip_zone


	mov		rax, [rsi + t_zone.size]
	cmp		rax, rcx
	je		.found


.skip_zone:
	mov		rax, [rsi + t_zone.next]
	test	rax, rax

	je		.allocate_zone

	mov		rsi, rax
	jmp		.loop_find_zone


.found:

	; On devrait essayer de choper la zone
	mov		rdx, rsi

	mov		rax, [rsi + t_zone.flag]
	cmp		rax, 0xf
	jbe		.first_block


	and		rax, -16
	mov		rsi, rax

	jmp		.loop_find_block
.first_block:
	add		rsi, t_zone.block
	;mov		qword [rsi + t_block.size], rdi
	; donc rsi = t_block[0]


.loop_find_block:

; ICI je devrais checker la taille.


.block_not_full:



	mov		rax, [rsi + t_block.next]
	test	rax, rax
	je		.empty_next
	sub		rax, rsi

	cmp		rdi, rax
	jae		.skip_block



.empty_next:
	mov		rax, [rsi + t_block.size]
	test	rax, rax
	je		.block_found
	jmp		.no_skip_block
.skip_block:
	mov		r11, 1
.no_skip_block:
	mov		rsi, [rsi + t_block.next]
	jmp		.loop_find_block

.block_found:

	mov		rax, [rdx + t_zone.numb]
	sub		rax, 32
	sub		rax, rdi
	sub		rax, rsi
	jnb		.block_valid	; donc ce check fonctionne il semblerait

	or byte [rdx + t_zone.flag], 0x2
	jmp		.loop_find_zone

.block_valid:


	mov		qword [rsi + t_block.size], rdi
	mov		r8, [rsi + t_block.next]


	mov		rax, rsi
	add		rax, 16
	add		rax, rdi


	mov		qword [rsi + t_block.next], rax
	test	r11, r11
	jnz		.no_flag
	and		qword [rdx + t_zone.flag], 0xf
	or		[rdx + t_zone.flag], rax
.no_flag:
	mov		r9, [rsi + t_block.next]
	cmp		r9, r8
	je		.skip_bla
	mov		[r9 + t_block.next], r8
.skip_bla:
	mov		rax, rsi	; renvoie la bonne addresse.
	add		rax, 16
.end:


	ret


.end_big:
	mov		[rsi + t_zone.numb], rsi
	add		qword [rsi + t_zone.numb], 32
	or		qword [rsi + t_zone.flag], 0x4
	ret
