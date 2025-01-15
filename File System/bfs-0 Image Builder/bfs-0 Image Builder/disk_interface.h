#pragma once
#include <fstream>
#include <iostream>
using namespace std;

class Disk 
{
private:
	fstream file;
	const unsigned int blocks;
public:
	Disk(const unsigned int& blocks, const char* file_path);
	~Disk();
	Disk(const Disk& d);
	int read_block(char* buffer, const unsigned int& block_num);
	int write_block(char* buffer, const unsigned int& block_num);
	void display();
};