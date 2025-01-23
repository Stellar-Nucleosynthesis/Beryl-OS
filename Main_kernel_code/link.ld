ENTRY(start)

SECTIONS
{
    KERNEL_VMA = 0xC0000000;
    KERNEL_LMA = 0x00100000;
    
    . = KERNEL_VMA + KERNEL_LMA;

    .text ALIGN(4K) : AT(ADDR(.text) - KERNEL_VMA)
    {
        *higher_half_mapper.o (.text)
        *(.text .text.*)
    }

    .rodata ALIGN(4K) : AT(ADDR(.rodata) - KERNEL_VMA)
    {
        *(.rodata .rodata.*)
    }

    .data ALIGN(4K) : AT(ADDR(.data) - KERNEL_VMA)
    {
        *(.data .data.*)
    }

    .bss ALIGN(4K) : AT(ADDR(.bss) - KERNEL_VMA)
    {
        *(COMMON)
        *(.bss .bss.*)
    }

    _kernel_start = KERNEL_VMA + KERNEL_LMA;
    _kernel_end = .;
}
