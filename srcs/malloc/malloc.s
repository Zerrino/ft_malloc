bits 64
default rel

%include "includes/malloc.inc"


section .text
        global	ft_malloc

; void	*(*ft_malloc)(size_t size)
;	rdi

ft_align:
	mov		rax, rdi
	dec		rax
	bsr		rcx, rdi
	test	rax, rdi
	setnz	dil
	movzx	rdi, dil
	inc		rdi
	shl		rdi, cl
	jmp		ft_malloc.aligned

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

	jmp		ft_align
.aligned:


	cmp		rdi, TINY_SIZE
	jle		ft_tiny
	cmp		rdi, SMALL_SIZE
	jle		ft_small




	mov		rax, rdi
.end:
	ret
