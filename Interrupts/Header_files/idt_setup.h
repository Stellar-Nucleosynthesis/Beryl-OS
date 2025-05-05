#ifndef IDT_SETUP_H
#define IDT_SETUP_H

#include "stdint.h"
#include "stdbool.h"

typedef struct __attribute__((packed))
{
	uint16_t size;
	uint32_t addr;
} idt_descriptor;

void load_idt(uint32_t idt_descriptor_addr);

typedef struct __attribute__((packed))
{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t zero;
	uint8_t type_attr : 5;
	uint8_t dpl : 2;
	uint8_t present : 1;
	uint16_t offset_high;
} idt_entry;

void fill_idt_entry(idt_entry* entry, uint16_t selector, uint32_t offset, uint8_t dpl, uint8_t present);

typedef struct __attribute__((packed))
{
	uint32_t ebp;
	uint32_t edi;
	uint32_t esi;
	uint32_t edx;
	uint32_t ecx;
	uint32_t ebx;
	uint32_t eax;
} cpu_state;

typedef struct __attribute__((packed))
{
	uint32_t error_code;
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
} stack_state;

void generic_interrupt_handler(cpu_state cpu_state, uint32_t int_num, stack_state stack_state);

bool ints_set();

void enable_ints();

void disable_ints();

#endif