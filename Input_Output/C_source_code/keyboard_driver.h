#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include "stdint.h"

//Returns true if data can be read from the keyboard
int kbd_data_available();

//Function for reading current keyboard scancode
uint8_t kbd_read_scancode();

//Function for converting scancode to lowercase ASCII
uint8_t scancode_to_ASCII(uint8_t scancode);

//Function for converting scancode to uppercase ASCII
char scancode_to_ASCII_uppercase(uint8_t scancode);

//Return true if the scancode indicates that the key was pressed
int scancode_key_pressed(uint8_t scancode);

#endif