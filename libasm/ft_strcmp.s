bits 64
default rel

section .text
        global  ft_strcmp

; rdi rsi
ft_strcmp:
		push	rbp
		mov		rbp, rsp
		xor		eax, eax
		test	rdi, rdi
		je ft_ret
		test	rsi, rsi
		je ft_ret
		mov		rcx, -1
		mov		r8, rdi
		repne	scasb
		mov		rdi, r8
		not		rcx
		repe	cmpsb
		movzx	eax, byte [rdi - 1]
		movzx	ecx, byte [rsi - 1]
		sub		eax, ecx
ft_ret:
		pop		rbp
	ret
