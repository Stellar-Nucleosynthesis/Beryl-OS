ENTRY(start)

SECTIONS
{
    . = 0x100000;
    
    .text : ALIGN(0x1000) {
        *c_runtime_env_loader.o(.text)
        *(.*)
    }
    
    .rodata : ALIGN(0x1000) {
        *(SORT_BY_ALIGNMENT(.rodata*))
    }
    
    .data : ALIGN(0x1000) {
        *(SORT_BY_ALIGNMENT(.data*))
    }
    
    .bss : ALIGN(0x1000) {
        *(SORT_BY_ALIGNMENT(.bss*))
    }
}