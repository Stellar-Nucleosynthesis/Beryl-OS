global load_gdt
global load_segment_selectors
global enter_protected_mode

section .text
align 0x4

;void load_gdt(uint32_t gdt_descriptor_addr);
load_gdt:
    mov eax, [esp + 4]
    lgdt [eax]
    ret

;void load_segment_selectors(uint16_t cs, uint16_t ds, uint16_t es, uint16_t ss);
load_segment_selectors:
    mov ax, [esp + 16]
    mov ss, ax
    mov ax, [esp + 12]
    mov es, ax
    mov ax, [esp + 8]
    mov ds, ax
    mov ax, [esp + 4]
    push eax
    push dummy_label
    retf
dummy_label:
    ret

;void enter_protected_mode();
enter_protected_mode:
    mov eax, cr0
    or eax, 0x00000001
    mov cr0, eax
    ret