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

unsigned long long int basic_gdt[5];
struct gdt_info basic_gdt_info;

void set_basic_gdt() 
{
    set_gdt_entry(basic_gdt, 0, 0, 0, 0); //NULL descriptor
    set_gdt_entry(basic_gdt + 1, 0, 0xFFFFF, 0x9A, 0xC); //Kernel code segment
    set_gdt_entry(basic_gdt + 2, 0, 0xFFFFF, 0x92, 0xC); //Kernel data segment
    set_gdt_entry(basic_gdt + 3, 0, 0xFFFFF, 0xFA, 0xC); //User mode code segment
    set_gdt_entry(basic_gdt + 4, 0, 0xFFFFF, 0xF2, 0xC); //User mode data segment

    basic_gdt_info.addr = (unsigned int)basic_gdt;
    basic_gdt_info.size = 39;

    load_gdt(&basic_gdt_info);
    load_segment_selectors(0x8, 0x10, 0x10, 0x10);
}