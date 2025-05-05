global load_idt
global ints_set
global enable_ints
global disable_ints

section .text
align 0x4

;void load_idt(uint32_t idt_descriptor_addr);
load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret

;bool ints_set();
ints_set:
    pushfd
    pop eax
    shr eax, 9
    and eax, 1
    ret
    
;void enable_ints();
enable_ints:
    sti
    ret

;void disable_ints();
disable_ints:
    cli
    ret