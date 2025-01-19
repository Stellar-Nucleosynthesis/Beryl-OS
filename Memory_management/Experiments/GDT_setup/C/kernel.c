#include "gdt.h"

#define GDT_SIZE 5

unsigned long long int gdt[GDT_SIZE];
struct gdt_info gdt_info;

void kmain() 
{
	set_gdt_entry(gdt, 0, 0, 0, 0); //NULL descriptor
	set_gdt_entry(gdt + 1, 0, 0xFFFFF, 0x9A, 0xC ); //Kernel code segment
	set_gdt_entry(gdt + 2, 0, 0xFFFFF, 0x92, 0xC ); //Kernel data segment
	set_gdt_entry(gdt + 3, 0, 0xFFFFF, 0xFA, 0xC ); //User mode code segment
	set_gdt_entry(gdt + 4, 0, 0xFFFFF, 0xF2, 0xC ); //User mode data segment

	gdt_info.addr = (unsigned int)gdt;
	gdt_info.size = GDT_SIZE * 8 - 1;

	load_gdt(&gdt_info);
	load_segment_selectors(0x8, 0x10, 0x10, 0x10);

	while (1);
}