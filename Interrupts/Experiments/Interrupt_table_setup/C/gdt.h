#ifndef GDT_H
#define GDT_H

//The structure which contains the address of GDT and its size
struct gdt_info 
{
	unsigned short size;
	unsigned int addr;
} __attribute__((packed));

//A function for constructing a GDT entry at a specified location with given parameters
void set_gdt_entry(unsigned long long int* ptr, unsigned int base, unsigned int limit, unsigned char access, unsigned char flags);

//A function for loading GDT. It is written in assembly
void load_gdt(struct gdt_info* ptr);

//A function for loading segment selectors in segment registers
void load_segment_selectors(unsigned short code, unsigned short data, unsigned short e_data, unsigned short stack);

//A function for loading GDT with 5 basic entries 
void set_basic_gdt();

#endif