#ifndef IO_PORT_ACCESS_H
#define IO_PORT_ACCESS_H

//An assembly-implemented function for writing a byte to an I/O port 
void outb(unsigned short port, unsigned char value);

//An assembly-implemented function for reading a byte from I/O port
unsigned char inb(unsigned short port);

//A function for waiting for a small period of time (1-4 microseconds) by issuing an I/O to an unused port
void io_wait() 
{ 
	outb(0x80, 0);
}

#endif