#ifndef GDT_SETUP_H
#define GDT_SETUP_H

#include "stdint.h"

typedef struct __attribute__((packed))
{
	uint16_t size;
	uint32_t addr;
} gdt_descriptor;

void load_gdt(uint32_t gdt_descriptor_addr);

typedef struct __attribute__((packed))
{
	uint64_t entry;
} gdt_entry;

void fill_gdt_entry(gdt_entry* entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

void load_segment_selectors(uint16_t cs, uint16_t ds, uint16_t es, uint16_t ss);

void enter_protected_mode();

#endif