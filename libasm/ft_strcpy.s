bits 64
default rel

section .text
        global  ft_strcpy

; rdi rsi
ft_strcpy:
	push	rbp
	mov		rbp, rsp
	mov		rax, rdi
	test	rdi, rdi
	jz		ft_ret
	test	rsi, rsi
	jz		ft_ret
	mov		r8, rdi
	mov		rdi, rsi
	xor		al, al
	mov		rcx, -1
	repne	scasb
	not		rcx
	mov		rdi, r8

	rep		movsb
	mov		rdi, r8
	mov		rax, rdi
ft_ret:
	pop	rbp
	ret
