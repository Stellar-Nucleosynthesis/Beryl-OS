#pragma once
#include "disk_interface.h"
#include "ofile.h"

typedef const unsigned int fd;

class bfs0 
{
private: 
	Disk disk;
	ofile* open_files[32]{};
	unsigned int current_dir;
	void init_data_structs();
public:
	bfs0(const unsigned int& blocks, const char* file_path);
	~bfs0();
	fd open(char* const filename);
	int close(fd descriptor);
	unsigned int lseek(fd descriptor, const unsigned int position);
	unsigned int read(fd descriptor, char* const buff, const unsigned int length);
	unsigned int write(fd descriptor, const char* const buff, const unsigned int length);
	int cd(char* dirname);
};