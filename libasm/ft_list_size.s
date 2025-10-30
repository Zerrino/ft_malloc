bits 64
default rel

section .text
		global	ft_list_size
; int		ft_list_size(t_list *); rdi

ft_list_size:
	push	rbp
	mov		rbp, rsp
	xor		eax, eax
	test	rdi, rdi
	je		ft_end
loop:
	inc		eax
	mov		rdi, [rdi + 8]
	test	rdi, rdi
	jne		loop


ft_end:
	pop		rbp
	ret
