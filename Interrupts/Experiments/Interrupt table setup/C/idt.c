#include "idt.h"
#include "io_port_access.h"

//PIC macros definition
#define PIC1_COMMAND 0x20       //PIC1 command port
#define PIC1_DATA	 0x21       //PIC1 data port
#define PIC2_COMMAND 0xA0       //PIC2 command port
#define PIC2_DATA	 0xA1       //PIC2 data port

#define PIC_EOI		 0x20	    //End of interrupt command

//Initialization command words definition
#define ICW1_INIT    0x10       //Puts PIC in initialization mode
#define ICW1_ICW4    0x01       //ICW4 will be used
#define ICW4_8086    0x01       //8086 mode will be used

void fill_idt_entry(struct idt_entry* entry, unsigned short selector, unsigned int offset, unsigned char dpl, unsigned char present)
{
    unsigned short offset_lo = offset & 0xFFFF;
    unsigned short offset_hi = (offset >> 16) & 0xFFFF;

    entry->offset_low = offset_lo;
    entry->offset_high = offset_hi;
    entry->selector = selector;
    entry->zero = 0;
    entry->present = present;
    entry->type_attr = 0b01110;
	entry->dpl = dpl;
}

void pic_remap(unsigned char offset1, unsigned char offset2)
{
	unsigned char mask1;
	unsigned char mask2;

	mask1 = inb(PIC1_DATA);                     //Saving masks
	mask2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  //Start the initialization sequence in cascade mode
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                   //ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, offset2);                   //ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 0b0100);                    //ICW3: Tell Master PIC that there is a slave PIC at IRQ2
	io_wait();
	outb(PIC2_DATA, 2);                         //ICW3: Tell Slave PIC its cascade identity (0000 0010)
	io_wait();

	outb(PIC1_DATA, ICW4_8086);                 //ICW4: Make the PICs use 8086 mode
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	outb(PIC1_DATA, mask1);                     //Restore saved masks
	outb(PIC2_DATA, mask2);
}

unsigned short pic_get_mask() {
	unsigned char mask1;
	unsigned char mask2;
	mask1 = inb(PIC1_DATA);
	mask2 = inb(PIC2_DATA);
	return (((unsigned short) mask2) << 8) | mask1;
}

void pic_set_mask(unsigned char mask1, unsigned char mask2) {
	outb(PIC1_DATA, mask1);
	outb(PIC2_DATA, mask2);
}

void generic_interrupt_handler(struct cpu_state cpu_state, unsigned int int_num, struct stack_state stack_state)
{
	ack_interrupt((unsigned int) int_num);      //Do nothing (for now) and acknowledge the interrupt
}

void ack_interrupt(unsigned char int_num)
{
	if (int_num < PIC1_INT_OFFSET || int_num > PIC2_INT_OFFSET + 7) return;
	if (int_num > PIC1_INT_OFFSET + 7) 
	{
		outb(PIC2_COMMAND, PIC_EOI);
	}
	outb(PIC1_COMMAND, PIC_EOI);
}