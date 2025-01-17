#ifndef IO_PORT_ACCESS_H
#define IO_PORT_ACCESS_H

void w_port(unsigned short port, unsigned char value);
unsigned char r_port(unsigned short port);

#endif