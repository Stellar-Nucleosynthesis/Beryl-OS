#include "stdint.h"
#include "idt.h"
#include "pic.h"

void fill_idt_entry(struct idt_entry* entry, uint16_t selector, uint32_t offset, uint8_t dpl, uint8_t present)
{
	uint16_t offset_lo = offset & 0xFFFF;
	uint16_t offset_hi = (offset >> 16) & 0xFFFF;

    entry->offset_low = offset_lo;
    entry->offset_high = offset_hi;
    entry->selector = selector;
    entry->zero = 0x0;
    entry->present = present & 0x1;
    entry->type_attr = 0b01110;
	entry->dpl = dpl & 0x3;
}

void generic_interrupt_handler(struct cpu_state cpu_state, uint32_t int_num, struct stack_state stack_state)
{
	pic_ack_interrupt(int_num & 0xFF);      //Do nothing (for now) and acknowledge the interrupt
}