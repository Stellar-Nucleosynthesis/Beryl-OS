#include "gdt.h"
#include "interrupt_handlers.h"
#include "idt.h"

#define IDT_SIZE             0xFF  //IDT size in x86

struct idt_entry IDT[IDT_SIZE];
struct idt_info idt_info;

void kmain() 
{
	set_basic_gdt();
	for (int i = 0; i < IDT_SIZE; i++) 
	{
		fill_idt_entry(IDT + i, 0x0, 0x0, 0x0, 0x0); //Filling IDT with invalid entries
	}
	fill_idt_entry(IDT + 0x21, 0x8, (unsigned int) & interrupt_handler_0x21, 0x0, 0x1); //Creating IDT entry for the keyboard
	idt_info.base = IDT;
	idt_info.size = IDT_SIZE * 8 - 1;
	pic_remap(PIC1_INT_OFFSET, PIC2_INT_OFFSET);
	load_idt(&idt_info);
	pic_set_mask(0b11111101, 0b11111111);           //Only interrupts from the keyboard are enabled
	if (!ints_set()) enable_ints();
	while (1);
}
