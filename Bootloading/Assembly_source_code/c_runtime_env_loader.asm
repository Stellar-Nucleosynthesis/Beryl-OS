global higher_half_start
extern kmain                                    ;Declaration of main kernel function function kmain

KERNEL_STACK_SIZE equ 0x100000                  ;Stack size

section .bss
align 0x4
kernel_stack:
    resb KERNEL_STACK_SIZE                      ;Allocating stack in .bss

section .text
align 0x4

higher_half_start:
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ;Initializing stack pointer
    mov ebp, kernel_stack + KERNEL_STACK_SIZE   ;Initializing base pointer
    push eax                                    ;Multiboot magic number
    push ebx                                    ;Multiboot info structure location
    call kmain                                  