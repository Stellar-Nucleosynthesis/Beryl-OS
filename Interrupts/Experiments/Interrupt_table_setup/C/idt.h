#ifndef IDT_H
#define IDT_H

//Macros for PIC remapping
#define PIC1_INT_OFFSET  0x20       //New PIC1 interrupt offset
#define PIC2_INT_OFFSET  0x28       //New PIC2 interrupt offset

//Structure, the pointer to which is passed to the CPU to load an IDT
struct idt_info{
	unsigned short size;
	void* base;
} __attribute__((packed));

//Load IDT table
void load_idt(struct idt_info* ptr);

struct idt_entry 
{
	unsigned short offset_low;
	unsigned short selector;
	unsigned char zero;
	unsigned char type_attr : 5;
	unsigned char dpl : 2;
	unsigned char present : 1;
	unsigned short offset_high;
} __attribute__((packed));

//Function for filling an IDT entry
void fill_idt_entry(struct idt_entry* entry, unsigned short selector, unsigned int offset, unsigned char dpl, unsigned char present);

//Function for remapping PIC interrupts
void pic_remap(unsigned char offset1, unsigned char offset2);

//Function for getting current PIC masks
unsigned short pic_get_mask();

//Fuction for setting PIC masks
void pic_set_mask(unsigned char mask1, unsigned char mask2);

//Parameters given to the generic interrupt handler
struct cpu_state {
	unsigned int ebp;
	unsigned int edi;
	unsigned int esi;
	unsigned int edx;
	unsigned int ecx;
	unsigned int ebx;
	unsigned int eax;
} __attribute__((packed));

struct stack_state {
	unsigned int error_code;
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;
} __attribute__((packed));

//Generic interrupt handler
void generic_interrupt_handler(struct cpu_state cpu_state, unsigned int int_num, struct stack_state stack_state);

//Function for acknowledging an interrupt
void ack_interrupt(unsigned char int_num);

//Function for checking whether interrupts are turned on
int ints_set();

//Function for enabling interrupts
void enable_ints();

//Function for disabling interrupts
void disable_ints();

#endif