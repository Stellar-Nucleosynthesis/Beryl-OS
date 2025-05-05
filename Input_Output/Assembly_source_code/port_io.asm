global outb
global inb
global io_wait

; void outb(uint16_t port, uint8_t val)
outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

; uint8_t inb(uint16_t port)
inb:
    mov dx, [esp + 4]
    in al, dx
    ret

; void io_wait()
io_wait:
    mov al, 0
    out 0x80, al
    ret