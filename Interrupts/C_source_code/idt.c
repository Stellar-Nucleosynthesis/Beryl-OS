#include "stdint.h"

#include "idt.h"
#include "pic.h"
#include "interrupt_operations.h"

#include "port_io.h"
#include "framebuffer_driver.h"
#include "keyboard_driver.h"

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

void keyboard_handler();

void page_fault_handler(uint32_t cs, uint32_t eip);

void generic_interrupt_handler(struct cpu_state cpu_state, uint32_t int_num, struct stack_state stack_state)
{
    switch (int_num) 
    {
    case 0x0E:
        page_fault_handler(stack_state.cs, stack_state.eip);
        break;
    case 0x21:
        keyboard_handler();
        break;
    }
	pic_ack_interrupt(int_num & 0xFF);
}

void keyboard_handler() 
{
    static int shift_active = 0;
    static int caps_lock_active = 0;
    if (kbd_data_available())
    {
        uint8_t scancode = kbd_read_scancode();

        if (scancode == 0x3A) //CAPS_LOCK pressed
        {
            caps_lock_active = !caps_lock_active;
            return;
        }

        if (scancode == 0x2A || scancode == 0x36) //SHIFT pressed
        {
            shift_active = 1;
            return;
        }

        if (scancode == 0xAA || scancode == 0xB6) //SHIFT released
        {
            shift_active = 0;
            return;
        }

        if (scancode_key_pressed(scancode))
        {
            if (caps_lock_active ^ shift_active) 
            {
                fb_write(scancode_to_ASCII_uppercase(scancode));
            } 
            else
            {
                fb_write(scancode_to_ASCII(scancode));
            }
        }
    }
}

void page_fault_handler(uint32_t cs, uint32_t eip)
{
    fb_write_string("Page fault: eip: ");
    fb_write_uint32(eip);
    fb_write_string("; cs: ");
    fb_write_uint32(cs);
    fb_write('\n');
    for (long long int i = 0; i < 1000000000; i++);
}