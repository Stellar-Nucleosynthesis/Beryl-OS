#include "stdint.h"
#include "port_io.h"

#define COMMAND_PORT 0x3D4
#define DATA_PORT    0x3D5

#define HIGH_BYTE    0xE
#define LOW_BYTE     0xF

#define ROWS         25
#define COLUMNS      80

int8_t* framebuffer = (int8_t*)0x000B8000;

int fb_get_cursor_position() 
{
	outb(COMMAND_PORT, HIGH_BYTE);
	uint8_t position_high_bits = inb(DATA_PORT);
	outb(COMMAND_PORT, LOW_BYTE);
	uint8_t position_low_bits = inb(DATA_PORT);
	uint16_t position = ((uint16_t)position_high_bits << 8) | position_low_bits;
	return position;
}

void fb_set_cursor(int position) 
{
	if (position < 0) position = 0;
	if (position > ROWS * COLUMNS - 1) position = ROWS * COLUMNS - 1;
	uint16_t pos = (uint16_t) position;
	outb(COMMAND_PORT, HIGH_BYTE);
	outb(DATA_PORT, (pos >> 8) & 0xFF);
	outb(COMMAND_PORT, LOW_BYTE);
	outb(DATA_PORT, pos & 0xFF);
}

void fb_move_cursor(int n) 
{
	int position = fb_get_cursor_position();
	fb_set_cursor(position + n);
}

void fb_write(char ch, uint8_t fg_color, uint8_t bg_color, uint8_t blink)
{
	int position = fb_get_cursor_position();
	if (position == ROWS * COLUMNS - 1) return;
	uint8_t color = 0;
	blink = (blink & 0x1) << 7;
	bg_color = (bg_color & 0x7) << 4;
	fg_color = (fg_color & 0xF);
	color = blink | bg_color | fg_color;
	framebuffer[position * 2] = ch;
	framebuffer[position * 2 + 1] = color;
	fb_set_cursor(position + 1);
}

void fb_set_background(uint8_t bg_color)
{
	bg_color = (bg_color & 0x7);
	uint8_t color = (bg_color << 4) | bg_color;
	for (int i = 0; i < ROWS; ++i) 
	{
		for (int j = 0; j < COLUMNS; ++j)
		{
			int position = i * COLUMNS + j;
			framebuffer[position * 2] = 'A';
			framebuffer[position * 2 + 1] = color;
		}
	}
}