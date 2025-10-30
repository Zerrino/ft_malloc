bits 64
default rel

section .text
		global	ft_list_sort
;void	ft_list_sort(t_list **, int (*cmp)());

; rdi rsi

;typedef struct			s_list
;{
;	void				*data;
;	struct s_list		*next;
;}						t_list;

ft_list_sort:
	push	rbp
	push	r15
	push	r14
	push	r13
	push	r12

	mov		rbp, rsp
	test	rdi, rdi
	jz		ft_end
	test	rsi, rsi
	jz		ft_end

	mov		r13, [rdi] ; list
	test	r13, r13
	jz		ft_end
	mov		r12, r13
	mov		r14, r13
	mov		r15, rsi ; func

.ext:
	mov		r13, r12
.loop:
	mov		r14, r13
	cmp	qword [r13 + 8],  0
	je		ft_end
.inside_loop:
	cmp	qword [r13 + 8],  0
	je		.end_loop


	mov		rdi, [r13]
	mov		rsi, [r13 + 8]
	mov		rsi, [rsi]

	call	r15

	test	eax, eax
	jle		.continue

	mov		rdi, [r13]
	mov		rcx, [r13 + 8]
	mov		rdx, [rcx]
	mov		[r13], rdx
	mov		[rcx], rdi

	jmp		.ext

.continue:
	mov		r13, [r13 + 8]
	jmp		.inside_loop
.end_loop:
	mov		r13, r14
	mov		r13, [r13 + 8]
	jmp		.loop
ft_end:

	pop		r12
	pop		r13
	pop		r14
	pop		r15
	pop		rbp
	ret
