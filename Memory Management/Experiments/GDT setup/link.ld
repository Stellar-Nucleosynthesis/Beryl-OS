ENTRY(start)

SECTIONS
{
    . = 0x100000;
    
    .text : {
        *env_builder.o(.text)
        *(.*)
    }
    
    .rodata : {
        *(SORT_BY_ALIGNMENT(.rodata*))
    }
    
    .data : {
        *(SORT_BY_ALIGNMENT(.data*))
    }
    
    .bss : {
        *(SORT_BY_ALIGNMENT(.bss*))
    }
}