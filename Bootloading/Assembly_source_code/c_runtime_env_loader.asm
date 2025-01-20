global start
extern kmain                                    ;Declaration of an external function kmain

KERNEL_STACK_SIZE equ 0x100000                  ;Stack size
MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x00000001                        ;Align modules
CHECKSUM equ -(MAGIC_NUMBER + FLAGS)

section .bss
align 0x4
kernel_stack:
    resb KERNEL_STACK_SIZE                      ;Allocating stack in .bss

section .text
align 0x4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM
start:
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ;Initializing stack pointer
    mov ebp, kernel_stack + KERNEL_STACK_SIZE   ;Initializing base pointer
    push ebx                                    ;Modules info structure location
    call kmain                                  