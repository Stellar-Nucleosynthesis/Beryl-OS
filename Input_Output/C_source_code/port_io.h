#ifndef PORT_IO_H
#define PORT_IO_H

#include "stdint.h"

//An assembly-implemented function for writing a byte to an I/O port 
void outb(uint16_t port, uint8_t value);

//An assembly-implemented function for reading a byte from I/O port
uint8_t inb(uint16_t port);

//A function for waiting for a small period of time (1-4 microseconds) by issuing an I/O to an unused port
void io_wait();

#endif