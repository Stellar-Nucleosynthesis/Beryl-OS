global load_gdt
global load_segment_selectors
global enter_protected_mode

section .text
align 0x4
load_gdt:
    mov eax, [esp + 4]
    lgdt [eax]
    ret

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

enter_protected_mode:
    mov eax, cr0
    or eax, 0x00000001
    mov cr0, eax
    ret