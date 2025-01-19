global load_gdt
global load_segment_selectors

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