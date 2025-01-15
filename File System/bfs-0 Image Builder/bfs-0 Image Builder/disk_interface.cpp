#include "disk_interface.h"

Disk::Disk(const unsigned int& blocks, const char* file_path) : blocks(blocks), file(file_path, ios::in | ios::out | ios::trunc)
{
	for (int i = 0; i < blocks * 512; ++i) 
	{
		file << static_cast<char>(0);
	}
}

Disk::~Disk(){}

int Disk::read_block(char* buffer, const unsigned int& block_num) 
{
	file.seekg(512 * block_num);
	if (file.fail()) return -1;
	file >> buffer;
	if (file.fail()) return -1;
	return 0;
}
int Disk::write_block(char* buffer, const unsigned int& block_num) 
{
	file.seekg(512 * block_num);
	if (file.fail()) return -1;
	file << buffer;
	if (file.fail()) return -1;
	return 0;
}

void Disk::display() 
{
	file.seekg(0);
	for (unsigned int i = 0; i < blocks; ++i) 
	{
		cout << "===Block " << i << "===\n";
		for(int j = 0; j < 32; ++j)
		{
			for (int k = 0; k < 16; ++k) 
			{
				char ch;
				file >> ch;
				cout << hex << static_cast<unsigned int>(ch) << " ";
			}
			cout << endl;
		}
	}
}