ENTRY(start)

SECTIONS
{
    KERNEL_VMA = 0xC0000000;
    KERNEL_LMA = 0x00100000;
    
    . = KERNEL_VMA + KERNEL_LMA;

    kernel_virtual_start = .;
    kernel_physical_start = . - 0xC0000000;

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

    kernel_virtual_end = .;
    kernel_physical_end = . - 0xC0000000;
}
