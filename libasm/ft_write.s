bits 64
default rel

section .text
        global  ft_write
        extern  __errno_location

; rdi, rsi, rdx

ft_empty:
    sub     rsp, 8
    call  __errno_location wrt ..plt
    add     rsp, 8
    mov  dword  [rax], 22
    mov     rax, -1
    jmp     ft_ret


ft_write:
	push	rbp
    push    r12
    mov		rbp, rsp
    test    rsi, rsi
    je      ft_empty
    mov     rax, 1
    syscall
    test    rax, rax
    js      ft_error
    jmp     ft_ret

ft_error:
    mov   r12d, eax
    neg   r12d
    sub   rsp, 8
    call  __errno_location wrt ..plt
    add   rsp, 8
    mov   dword [rax], r12d
    mov   rax, -1

ft_ret:
    pop r12
    pop rbp
	ret
