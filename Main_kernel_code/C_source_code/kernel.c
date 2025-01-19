#include "stdint.h"
#include "gdt.h"
#include "pic.h"
#include "interrupt_operations.h"
#include "interrupt_handlers.h"
#include "idt.h"

#define GDT_SIZE  0x03  //Only 3 entries are needed for a basic GDT
#define IDT_SIZE  0xFF  //IDT size in x86             

uint64_t GDT[GDT_SIZE];
struct gdt_descriptor gdt_descr;

struct idt_entry IDT[IDT_SIZE];
struct idt_descriptor idt_descr;

void kmain() 
{
	fill_gdt_entry(GDT, 0x0, 0x0, 0x0, 0x0);           //NULL segment
	fill_gdt_entry(GDT + 1, 0x0, 0xFFFFF, 0x9A, 0xC);  //Kernel code segment
	fill_gdt_entry(GDT + 2, 0x0, 0xFFFFF, 0x92, 0xC);  //Kernel data segment
	gdt_descr.addr = (uint32_t) GDT;
	gdt_descr.size = GDT_SIZE * 8 - 1;
	load_gdt(&gdt_descr);
	load_segment_selectors(0x8, 0x10, 0x10, 0x10);


	for (int i = 0; i < IDT_SIZE; ++i) 
	{
		fill_idt_entry(IDT + i, 0x0, 0x0, 0x0, 0x0);   //Filling IDT with invalid entries
	}
	fill_idt_entry(IDT + 0x21, 0x8, (unsigned int) & interrupt_handler_0x21, 0x0, 0x1); //Creating IDT entry for the keyboard
	idt_descr.addr = (uint32_t) IDT;
	idt_descr.size = IDT_SIZE * 8 - 1;
	load_idt(&idt_descr);

	pic_remap(PIC1_INT_OFFSET, PIC2_INT_OFFSET);
	pic_set_mask(0b11111101, 0b11111111);           //Only interrupts from the keyboard are enabled

	if (!ints_set()) enable_ints();
	while (1);
}
