#include <stdint.h>
#include "gdt.h"

void fill_gdt_entry(void* ptr, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    uint8_t* target = (uint8_t*)ptr;

    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] = (limit >> 16) & 0x0F;

    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    target[5] = access;

    target[6] |= (flags << 4);
}