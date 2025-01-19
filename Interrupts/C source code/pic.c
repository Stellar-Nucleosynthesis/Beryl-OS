#include <stdint.h>

//PIC macros definition
#define PIC1_COMMAND 0x20       //PIC1 command port
#define PIC1_DATA	 0x21       //PIC1 data port
#define PIC2_COMMAND 0xA0       //PIC2 command port
#define PIC2_DATA	 0xA1       //PIC2 data port

#define PIC_EOI		 0x20	    //End of interrupt command

//Initialization command words definition
#define ICW1_INIT    0x10       //Put PIC in initialization mode
#define ICW1_ICW4    0x01       //ICW4 will be used
#define ICW4_8086    0x01       //8086 mode will be used

void pic_remap(uint8_t offset1, uint8_t offset2)
{
	uint8_t mask1 = inb(PIC1_DATA);             //Saving masks
	uint8_t mask2 = inb(PIC2_DATA);

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

uint8_t pic1_get_mask() {
	return inb(PIC1_DATA);
}

uint8_t pic2_get_mask() {
	return inb(PIC2_DATA);
}

void pic_set_mask(uint8_t mask1, uint8_t mask2) {
	outb(PIC1_DATA, mask1);
	outb(PIC2_DATA, mask2);
}

void pic_ack_interrupt(uint8_t int_num)
{
	if (int_num < PIC1_INT_OFFSET || int_num > PIC2_INT_OFFSET + 7) return;
	if (int_num > PIC1_INT_OFFSET + 7)
	{
		outb(PIC2_COMMAND, PIC_EOI);
	}
	outb(PIC1_COMMAND, PIC_EOI);
}