bits 64
default rel

section .text
		global	ft_list_push_front
		extern  ft_create_elem


; void ft_list_push_front(t_list **begin_list, void *data);

ft_list_push_front:
	push	rbp
	mov		rbp, rsp
	test	rdi, rdi
	je		ft_end

	push	rdi
	mov		rdi, rsi
	sub		rsp, 8
	call	ft_create_elem
	add		rsp, 8
	pop		rdi

	test	rax, rax
	je		ft_end
	mov		r8, [rdi]
	mov		[rdi], rax
	mov		[rax + 8], r8



ft_end:
	pop		rbp
	ret
