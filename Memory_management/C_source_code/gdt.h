#ifndef GDT_H
#define GDT_H

#include "stdint.h"

//The structure which contains the address of GDT and its size
struct gdt_descriptor 
{
	uint16_t size;
	uint32_t addr;
} __attribute__((packed));

//Function for constructing a GDT entry in specified place with given parameters
void fill_gdt_entry(void* ptr, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

//Function for loading GDT. It is written in assembly
void load_gdt(uint32_t gdt_descriptor_ptr);

//Function for loading segment selectors in segment registers
void load_segment_selectors(uint16_t cs_selector, uint16_t ds_selector, uint16_t es_selector, uint16_t ss_selector);

//Function for entering 32-bit protected mode
void enter_protected_mode();

#endif