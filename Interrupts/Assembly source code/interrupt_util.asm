global load_idt
global ints_set
global enable_ints
global disable_ints

section .text
align 0x4

load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret

ints_set:
    pushfd
    pop eax
    shr eax, 9
    and eax, 1
    ret
    
enable_ints:
    sti
    ret

disable_ints:
    cli
    ret