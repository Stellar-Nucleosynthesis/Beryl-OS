#include "gdt.h"

void set_gdt_entry(unsigned long long int* ptr, unsigned int base, unsigned int limit, unsigned char access, unsigned char flags)
{
    unsigned char* target = (unsigned char*)ptr;
    // Encode the limit
    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] = (limit >> 16) & 0x0F;

    // Encode the base
    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    // Encode the access byte
    target[5] = access;

    // Encode the flags
    target[6] |= (flags << 4);
}