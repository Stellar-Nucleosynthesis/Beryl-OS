#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include "stdint.h"
#include "stdbool.h"

bool kbd_data_available();

uint8_t kbd_read_scancode();

char scancode_to_ASCII(uint8_t scancode);

char scancode_to_ASCII_uppercase(uint8_t scancode);

bool scancode_key_pressed(uint8_t scancode);

#endif