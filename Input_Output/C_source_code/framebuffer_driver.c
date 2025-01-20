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

void fb_write(char ch)
{
	int position = fb_get_cursor_position();
	if (position == ROWS * COLUMNS - 1) return;

	if (ch == '\n') 
	{
		int row = position / COLUMNS;
		if (row == ROWS - 1) return;
		fb_set_cursor((row + 1) * COLUMNS);
		return;
	}

	if (ch == '\b')
	{
		int column = position % COLUMNS;
		int row = position / COLUMNS;
		fb_set_cursor(--position);
		framebuffer[position * 2] = ' ';
		if (column == 0 && row != 0) 
		{
			while (framebuffer[(position - 1) * 2] == ' ' && position != 0) 
			{
				fb_set_cursor(--position);
			}
		}
		return;
	}

	framebuffer[position * 2] = ch;
	fb_set_cursor(position + 1);
}

void fb_write_string(char* ch)
{
	int count = 0;
	while (ch[count] != 0) 
	{
		fb_write(ch[count++]);
	}
}

void fb_set_color(uint8_t bg_color, uint8_t fg_color, uint8_t blink)
{
	bg_color = (bg_color & 0x7) << 4;
	fg_color = fg_color & 0xF;
	blink = (blink & 0x1) << 7;
	uint8_t color = blink | bg_color | fg_color;
	for (int i = 0; i < ROWS; ++i) 
	{
		for (int j = 0; j < COLUMNS; ++j)
		{
			int position = i * COLUMNS + j;
			framebuffer[position * 2] = ' ';
			framebuffer[position * 2 + 1] = color;
		}
	}
}