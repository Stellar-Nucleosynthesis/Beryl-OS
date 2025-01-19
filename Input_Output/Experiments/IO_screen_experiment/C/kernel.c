#include "colors.h"
#include "io_port_access.h"

#define COMMAND_PORT 0x3D4
#define DATA_PORT 0x3D5

#define HIGH_BYTE 14
#define LOW_BYTE 15

char* framebuffer = (char*) 0x000B8000; //Video buffer address

void set_cell(int row, int column, char ch, char background, char foreground)
{
	int offset = 2 * (row * 80 + column);
	char color = 0;
	color |= (background & 0x7) << 4;
	color |= foreground & 0xF;
	framebuffer[offset] = ch;
	framebuffer[offset + 1] = color;
}

void set_cursor(unsigned char row, unsigned char column) 
{
	unsigned short position = row * 80 + column;
	w_port(COMMAND_PORT, HIGH_BYTE);
	w_port(DATA_PORT, (position >> 8) & 0xFF);
	w_port(COMMAND_PORT, LOW_BYTE);
	w_port(DATA_PORT, position & 0xFF);
}

void kmain() 
{
	for (int i = 0; i < 80; i++) 
	{
		for (int j = 0; j < 25; j++) 
		{
			set_cell(j, i, 'A', LIGHT_GREY, RED);
		}
	}
	set_cursor(0, 0);
	while (1);
}