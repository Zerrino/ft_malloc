bits 64
default rel

section	.data
	buffer:     times 256 db 0

section .text
        global	ft_atoi_base

; int			ft_atoi_base(char *str, char *base);
; rdi rsi


ft_atoi_base:
	push	rbp
	mov		rbp, rsp
	xor		eax, eax
	test	rdi, rdi
	je		ft_end
	test	rsi, rsi
	je		ft_end

	push	rdi
	push	rsi
	lea		rdi, [rel buffer]
	mov		rcx, 256
	xor		al, al
	rep		stosb
	pop		rsi
	pop		rdi


	xchg	rdi, rsi

	xor		r8, r8
	lea		r9, [rel buffer]

loop_base:
	movzx	rcx, byte [rdi + r8]
	test	cl, cl
	jz		end_loop

	cmp		byte [r9 + rcx], 0
	jne		ft_end

	mov		byte [r9 + rcx], r8b
	inc		byte [r9 + rcx]


	cmp		cl, 9
	jb		ok
	cmp		cl, 13
	ja		ok
	jmp		ft_end

ok:
	cmp		cl, ' '
	je		ft_end
	cmp		cl, '+'
	je		ft_end
	cmp		cl, '-'
	je		ft_end
	inc		r8
	jmp		loop_base
end_loop:
	cmp		r8, 2
	js		ft_end
	mov		r11, r8
	mov		rcx, -1
	mov		al, ' '
	mov		rdi, rsi
	repe	scasb
	dec		rdi
	; cleaning of spaces

	; sign on r10
	mov		r10, 1
loop_sign:
	mov		al, byte [rdi]
	test	al, al
	jz		ft_end
	cmp		al, '+'
	je		loop_sign_continue
	cmp		al, '-'
	jne		loop_end_sign
	imul	r10d, -1
loop_sign_continue:
	inc		rdi
	jmp		loop_sign
loop_end_sign:
	xor		r8, r8
	xor		eax, eax
	xor		rsi, rsi
loop_atoi:
	movzx	rcx, byte [rdi + r8]
	test	cl, cl
	jz		ft_end
	cmp		byte [r9 + rcx], 0
	je		ft_end

	mov		sil, byte [r9 + rcx]
	dec		sil
	imul	rax, r11
	add		rax, rsi

	inc		r8
	jmp		loop_atoi
ft_end:
	imul	rax, r10
	pop		rbp
	ret
