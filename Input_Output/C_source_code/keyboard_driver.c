#include "stdint.h"
#include "stdbool.h"
#include "port_io.h"

#define KBD_DATA_PORT    0x60
#define KBD_STATUS_PORT  0x64
#define SCANCODE_RELEASE 0x80  //Scancode of a released key

static const char scancode_to_ascii[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0,
};

static const char scancode_to_ascii_uppercase[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' ', 0,
};

bool kbd_data_available() 
{
	uint8_t status_byte = inb(KBD_STATUS_PORT);
    return status_byte & 0x1;
}

uint8_t kbd_read_scancode() 
{
	return inb(KBD_DATA_PORT);
}

char scancode_to_ASCII(uint8_t scancode) 
{
    if (scancode < sizeof(scancode_to_ascii))
        return scancode_to_ascii[scancode & 0x7F];

    return 0;
}

char scancode_to_ASCII_uppercase(uint8_t scancode)
{
    if (scancode < sizeof(scancode_to_ascii_uppercase))
        return scancode_to_ascii_uppercase[scancode & 0x7F];

    return 0;
}

bool scancode_key_pressed(uint8_t scancode)
{
    return !(scancode & SCANCODE_RELEASE);
}