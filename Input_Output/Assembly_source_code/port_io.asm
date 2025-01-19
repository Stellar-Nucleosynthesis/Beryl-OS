global outb
global inb
global io_wait

section .text
align 0x4
outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

inb:
    mov dx, [esp + 4]
    in al, dx
    ret

io_wait:
    mov al, 0
    mov dx, 0x80
    out dx, al
    ret
