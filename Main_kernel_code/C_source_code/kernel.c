#include "stdint.h"

#include "framebuffer_driver.h"

#include "gdt_setup.h"
#include "paging.h"
#include "kernel_memory_allocator.h"

#include "idt_setup.h"
#include "interrupt_handlers.h"
#include "pic_setup.h"

#include "multiboot.h"

#define GDT_SIZE  0x03  //Only 3 entries are needed for a basic GDT
#define IDT_SIZE  0xFF  //IDT size in x86    
#define PD_SIZE   0x400 //PD size in x86

gdt_entry GDT[GDT_SIZE];
gdt_descriptor gdt_descr;

idt_entry IDT[IDT_SIZE];
idt_descriptor idt_descr;

uint32_t kernel_PD[PD_SIZE] __attribute__((aligned(4096)));

void setup_segmentation()
{
	fill_gdt_entry(GDT, 0x0, 0x0, 0x0, 0x0);           //NULL segment
	fill_gdt_entry(GDT + 1, 0x0, 0xFFFFF, 0x9A, 0xC);  //Kernel code segment
	fill_gdt_entry(GDT + 2, 0x0, 0xFFFFF, 0x92, 0xC);  //Kernel data segment
	gdt_descr.addr = (uint32_t)GDT;
	gdt_descr.size = GDT_SIZE * 8 - 1;
	load_gdt((uint32_t)&gdt_descr);
	load_segment_selectors(0x8, 0x10, 0x10, 0x10);
}

void setup_interrupt_table()
{
	for (int i = 0; i < IDT_SIZE; ++i)
	{
		fill_idt_entry(IDT + i, 0x0, 0x0, 0x0, 0x0);   //Filling IDT with invalid entries
	}
	fill_idt_entry(IDT + 0x0E, 0x8, (uint32_t)&interrupt_handler_0xE, 0x0, 0x1);  //Creating IDT entry for page fault
	fill_idt_entry(IDT + 0x21, 0x8, (uint32_t)&interrupt_handler_0x21, 0x0, 0x1); //Creating IDT entry for the keyboard
	idt_descr.addr = (uint32_t)IDT;
	idt_descr.size = IDT_SIZE * 8 - 1;
	load_idt((uint32_t)&idt_descr);
}

void configure_pic()
{
	pic_remap(PIC1_INT_OFFSET, PIC2_INT_OFFSET);
	pic1_set_mask(0b11111101);           //Only IRQs from the keyboard are enabled
	pic2_set_mask(0b11111111);           //Only IRQs from the keyboard are enabled
}

void setup_new_pd()
{
	for (int i = 0; i < PD_SIZE; ++i)
	{
		kernel_PD[i] = 0x00000000;
	}
	fill_pde_large((pde_large*)(kernel_PD + 0x300), 0x00000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1);
	load_pd(get_phys_addr((uint32_t)&kernel_PD));
}

void display_memory_info(uint32_t multiboot_info_addr, uint32_t multiboot_magic)
{
	if (multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC) 
	{
		fb_write_string("Invalid multiboot structure!\n");
		return;
	}

	multiboot_info_addr += KERNEL_OFFSET;
	multiboot_info_t* multiboot_info_ptr = (multiboot_info_t*)multiboot_info_addr;

	fb_write_string("Available memory: ");
	fb_write_uint32(multiboot_info_ptr->mem_lower);
	fb_write('-');
	fb_write_uint32(multiboot_info_ptr->mem_upper);
	fb_write('\n');

	if (!(multiboot_info_ptr->flags >> 6 & 0x1))
	{
		fb_write_string("Invalid memory map!\n");
		return;
	}

	fb_write_string("Free memory regions: \n");

	uint32_t mmap_length = multiboot_info_ptr->mmap_length;
	uint32_t mmap_addr = multiboot_info_ptr->mmap_addr;
	multiboot_memory_map_t* mmap_ptr = (multiboot_memory_map_t*)(mmap_addr + KERNEL_OFFSET);

	for (uint32_t offset = 0; offset < mmap_length;)
	{
		multiboot_memory_map_t* entry = (multiboot_memory_map_t*)((uint8_t*)mmap_ptr + offset);

		if (entry->type == 1) 
		{
			fb_write_string("Address: ");
			fb_write_uint32((uint32_t)entry->addr_low);
			fb_write('\n');
			fb_write_string("Length: ");
			fb_write_uint32((uint32_t)entry->len_low);
			fb_write('\n');
			fb_write('\n');
		}

		offset += entry->size + sizeof(entry->size);
	}
}

extern uint8_t kernel_virtual_start;
extern uint8_t kernel_physical_start;
extern uint8_t kernel_virtual_end;
extern uint8_t kernel_physical_end;

void kmain(uint32_t multiboot_info_addr, uint32_t multiboot_magic)
{
	if(ints_set()) disable_ints();
	setup_segmentation();
	setup_interrupt_table();
	configure_pic();
	if (!ints_set()) enable_ints();
	setup_new_pd();

	fb_set_color(LIGHT_GREY, RED, NO_BLINK);
	fb_set_cursor(0);

	if (multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		fb_write_string("Invalid multiboot structure!\n");
	}
	else
	{
		multiboot_info_addr += KERNEL_OFFSET;
		multiboot_info_t* multiboot_info_ptr = (multiboot_info_t*)multiboot_info_addr;

		fb_write_string("Available memory: ");
		fb_write_uint32(multiboot_info_ptr->mem_lower);
		fb_write('-');
		fb_write_uint32(multiboot_info_ptr->mem_upper);
		fb_write('\n');
	}

	uint32_t heap_start_addr = (uint32_t)&kernel_virtual_end;
	uint32_t heap_end_addr = 0xC0400000 - 1;

	fb_write_string("Kernel virtual space: ");
	fb_write_uint32((uint32_t)&kernel_virtual_start);
	fb_write('-');
	fb_write_uint32((uint32_t)&kernel_virtual_end);
	fb_write('\n');
	fb_write_string("Kernel physical space: ");
	fb_write_uint32((uint32_t)&kernel_physical_start);
	fb_write('-');
	fb_write_uint32((uint32_t)&kernel_physical_end);
	fb_write('\n');
	fb_write_string("Kernel heap virtual space: ");
	fb_write_uint32(heap_start_addr);
	fb_write('-');
	fb_write_uint32(heap_end_addr);
	fb_write('\n');

	/*int heap_init_res = init_kernel_memory_allocator(heap_start_addr, heap_end_addr, kernel_PD, 0x3FF);
	fb_write_string("Kernel heap initialization result: ");
	fb_write_uint32((uint32_t)heap_init_res);
	fb_write('\n');
	void* kmalloc1_res = kmalloc(20);
	fb_write_string("kmalloc result (20 bytes): ");
	fb_write_uint32((uint32_t)kmalloc1_res);
	fb_write('\n');
	void* kmalloc2_res = kmalloc(40);
	fb_write_string("kmalloc result (40 bytes): ");
	fb_write_uint32((uint32_t)kmalloc2_res);
	fb_write('\n');*/
	while (1);
}
