global load_pd
global enable_paging
global enable_large_pages

section .text
align 0x4

load_pd:
    mov eax, [esp + 4]
    mov cr3, eax
    mov eax, eax  ;Dummy operation
    ret

enable_paging:
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    ret

enable_large_pages:
    mov eax, cr4
    or eax, 0x00000010
    mov cr4, eax
    ret