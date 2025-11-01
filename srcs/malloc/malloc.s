bits 64
default rel

%include "includes/malloc.inc"

section .bss
	g_global: resq 1

section .text
        global	ft_malloc

; void	*(*ft_malloc)(size_t size)
;	rdi


ft_tiny:





	mov		rax, rdi
	ret

ft_small:


	mov		rax, rdi
	ret



ft_malloc:
	xor		rax, rax
	test	rdi, rdi
	jz		.end
	; --- TO-DO ---

	; CHECKER SI SUPERIEUR A SMALL BLOCK

	; --- ALIGNEMENT ---
	mov		rax, rdi
	dec		rax
	bsr		rcx, rdi
	test	rax, rdi
	setnz	dil
	movzx	rdi, dil
	inc		rdi
	shl		rdi, cl
	; --- ALIGNE --- CL STILL NUMBER

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
	push	rdi
	push	rcx

	mov		rax, SYS_mmap
	mov		rdi, 0
	mov		rsi, rcx
	shl		rsi, 8
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


	jmp		.continue
.g_global_exit:

	mov		rsi, [rsi]

	mov		rdx, [rsi + t_zone.next]
	test	rdx, rdx
	je		.allocate_next


	jmp		.g_global_exit

.allocate_next:
	mov		qword [rsi + t_zone.next], rax
	mov		rsi, [rsi + t_zone.next]

.continue:

	mov		qword [rsi + t_zone.size], rcx
	mov		qword [rsi + t_zone.next], 0

.not_empty:
	lea		rsi, [rel g_global]
	mov		rsi, [rsi]

.loop_find_zone:
	mov		rax, [rsi + t_zone.size]
	cmp		rax, rcx
	je		.found
	mov		rax, [rsi + t_zone.next]
	test	rax, rax
	je		.allocate_zone
	mov		rsi, rax
	jmp		.loop_find_zone

.found:

	lea		rax, [rel g_global]
	mov		rax, [rax]
.end:
	ret
