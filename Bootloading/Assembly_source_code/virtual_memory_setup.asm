global start
extern kmain_start

PAGE_DIR_SIZE equ 0x1000
PAGE_PRESENT_FLAG equ 0x01
PAGE_RW_FLAG equ 0x02
PAGE_SIZE_FLAG equ 0x80
PAGE_FLAGS equ PAGE_PRESENT_FLAG | PAGE_RW_FLAG | PAGE_SIZE_FLAG

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
    mov edx, PAGE_FLAGS | 0x00000000        ;EAX and EBX contain multiboot information and must not be used!

    mov ecx, page_directory - 0xC0000000    ;Real page directory address
    mov [ecx + 0x000], edx                  ;Mapping vpn 0x000 to the first pf
    mov [ecx + 0xC00], edx                  ;Mapping vpn 0x300 to the first pf

    mov cr3, ecx                            ;Setting PD address

    mov edx, cr4                            ;Enabling PSE          
    or edx, 0x00000010
    mov cr4, edx

    mov edx, cr0                            ;Enabling paging
    or edx, 0x80000000
    mov cr0, edx

    jmp kmain_start + 0xC0000000            ;Jumping to higher half