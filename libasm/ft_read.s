bits 64
default rel

section .text
        global	ft_read
		extern	__errno_location

ft_read:
		push	rbp
		mov		rbp, rsp
        xor		rax, rax
        syscall
        test    rax, rax
        js      ft_error
        jmp     ft_ret
ft_error:
        mov		r8, rax
        push    r8
        sub     rsp, 8
        call	__errno_location  wrt ..plt
        add     rsp, 8
        pop     r8
        neg		r8
        mov		[rax], r8
        mov		rax, -1
ft_ret:
        pop     rbp
                ret
