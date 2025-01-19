#ifndef IDT_H
#define IDT_H

#include <stdint.h>

//Macros for PIC remapping
#define PIC1_INT_OFFSET  0x20       //New PIC1 interrupt offset
#define PIC2_INT_OFFSET  0x28       //New PIC2 interrupt offset

//The structure which contains the address of IDT and its size
struct idt_descriptor
{
	uint16_t size;
	uint32_t addr;
} __attribute__((packed));

//Load IDT table
void load_idt(struct idt_descriptor* ptr);

struct idt_entry 
{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t zero;
	uint8_t type_attr : 5;
	uint8_t dpl : 2;
	uint8_t present : 1;
	uint16_t offset_high;
} __attribute__((packed));

//Function for filling an IDT entry
void fill_idt_entry(struct idt_entry* entry, uint16_t selector, uint32_t offset, uint8_t dpl, uint8_t present);

//Parameters given to the generic interrupt handler
struct cpu_state {
	uint32_t ebp;
	uint32_t edi;
	uint32_t esi;
	uint32_t edx;
	uint32_t ecx;
	uint32_t ebx;
	uint32_t eax;
} __attribute__((packed));

struct stack_state {
	uint32_t error_code;
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
} __attribute__((packed));

//Generic interrupt handler
void generic_interrupt_handler(struct cpu_state cpu_state, uint32_t int_num, struct stack_state stack_state);

#endif