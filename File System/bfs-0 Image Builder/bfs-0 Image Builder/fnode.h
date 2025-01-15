#pragma once

typedef unsigned char byte;

struct fnode 
{
	unsigned int size;
	unsigned int create_time;
	unsigned int change_time;
	unsigned short permissions : 12;
	unsigned short type : 4;
	byte links;
	byte reserved;
	unsigned int block_links[124];
};