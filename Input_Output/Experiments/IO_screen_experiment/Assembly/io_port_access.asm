global w_port
global r_port

section .text
align 0x4
w_port:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

r_port:
    mov dx, [esp + 4]
    in al, dx
    ret
