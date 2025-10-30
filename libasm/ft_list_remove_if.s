bits 64
default rel

section .text
		global	ft_list_remove_if
		extern	free

;ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
; rdi rsi rdx rcx
ft_list_remove_if:
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
	test	rdx, rdx
	jz		ft_end
	test	rcx, rcx
	jz		ft_end
	test	rdi, rdi
	jz		ft_end

	mov		r12, rdi
	xor		r13, r13		; last
	mov		r14, [r12]		; present
	test	r14, r14
	jz		ft_end
	mov		r15, [r14 + 8]	; next

.loop_check_start:
	cmp	qword [r14],  0
	je		.check_last

	push	rsi
	push	rdx
	push	rcx
	sub		rsp, 8

	mov		rdi, [r14]
	mov		rsi, rsi

	call	rdx

	add		rsp, 8
	pop		rcx
	pop		rdx
	pop		rsi

	test	eax, eax
	jnz		.no_delete


	push	rsi
	push	rdx
	push	rcx
	sub		rsp, 8

	mov		rdi, [r14]
	call	rcx
	mov		rdi, r14
	call	free	wrt ..plt

	add		rsp, 8
	pop		rcx
	pop		rdx
	pop		rsi




	test	r13, r13
	jnz		.no_null
	xor		r13, r13
	mov		[r12], r15
	test	r15, r15
	jz		ft_end
	mov		r14, [r12]		; present
	mov		r15, [r14 + 8]	; next

	jmp		.loop_check_start
.no_null:
	;	r13 last
	;	r14 present
	;	r15 next
	mov		rax, r15
	mov		[r13 + 8], rax

	test	r15, r15
	jz		ft_end

	mov		r14, r15
	mov		r15, [r14 + 8]


	jmp		.loop_check_start
.no_delete:

	mov		r13, r14		; last
	mov		r14, [r14 + 8]	; present
	test	r14, r14
	jz		ft_end
	mov		r15, [r14 + 8]	; next

	jmp		.loop_check_start


.check_last:


ft_end:
	xor		rax, rax

	pop		r12
	pop		r13
	pop		r14
	pop		r15
	pop		rbp
	ret
