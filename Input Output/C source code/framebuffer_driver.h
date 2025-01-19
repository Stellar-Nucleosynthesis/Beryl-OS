#ifndef FRAMEBUFFER_DRIVER_H
#define FRAMEBUFFER_DRIVER_H

#include <stdint.h>

#define BLACK         0x0
#define BLUE          0x1
#define GREEN         0x2
#define CYAN          0x3
#define RED           0x4
#define MAGENTA       0x5
#define BROWN         0x6
#define LIGHT_GREY    0x7

#define DARK_GREY     0x8
#define LIGHT_BLUE    0x9
#define LIGHT_GREEN   0xA
#define LIGHT_CYAN    0xB
#define LIGHT_RED     0xC
#define LIGHT_MAGENTA 0xD
#define LIGHT_BROWN   0xE
#define WHITE         0xF

#define BLINK         0x1
#define NO_BLINK      0x0

//Functions for getting the current cursor position 
int fb_get_cursor_position();

//Function for setting cursor position
void fb_set_cursor(int position);

//Function for moving cursor n times forwards (or backwards, if the value is negative)
void fb_move_cursor(int n)

//Function for writing a character and advancing the cursor one position forward
void fb_write(char ch, uint8_t fg_color, uint8_t bg_color, uint8_t blink);

//Function for setting background color
void fb_set_background(uint8_t bg_color);

#endif