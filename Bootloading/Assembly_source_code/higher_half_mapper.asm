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
    mov edx, PAGE_FLAGS | 0x00000000           ;EAX and EBX contain multiboot information and must not be used!

    mov ecx, page_directory - 0xC0000000
    mov [ecx + 0x000], edx
    mov [ecx + 0xC00], edx

    mov edx, cr4
    or edx, 0x00000010
    mov cr4, edx

    mov cr3, ecx

    mov edx, cr0
    or edx, 0x80000000
    mov cr0, edx

    jmp higher_half_start + 0xC0000000