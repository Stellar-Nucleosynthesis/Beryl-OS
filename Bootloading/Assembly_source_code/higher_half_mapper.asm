global start
extern higher_half_start

PAGE_DIR_SIZE equ 0x1000
PAGE_PRESENT equ 0x01
PAGE_RW equ 0x02
PAGE_SIZE equ 0x80
PAGE_FLAGS equ PAGE_PRESENT | PAGE_RW | PAGE_SIZE

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x00000001                            ; Align modules
CHECKSUM equ -(MAGIC_NUMBER + FLAGS)

section .bss
align 0x1000
page_directory:
    resb PAGE_DIR_SIZE

section .text
align 0x4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

start:
    mov eax, PAGE_FLAGS | 0x00000000
    mov ebx, page_directory - 0xC0000000
    mov [ebx + 0x000], eax
    mov [ebx + 0xC00], eax

    mov eax, cr4
    or eax, 0x00000010
    mov cr4, eax

    mov eax, ebx
    mov cr3, eax

    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    call higher_half_start