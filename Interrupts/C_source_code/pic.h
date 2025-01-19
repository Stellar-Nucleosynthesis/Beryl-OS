#ifndef PIC_H
#define PIC_H

#include "stdint.h"

//Macros for PIC remapping
#define PIC1_INT_OFFSET  0x20       //New PIC1 interrupt offset
#define PIC2_INT_OFFSET  0x28       //New PIC2 interrupt offset

//Function for remapping PIC interrupts
void pic_remap(uint8_t offset1, uint8_t offset2);

//Functions for getting current PIC masks
uint8_t pic1_get_mask();

uint8_t pic2_get_mask();

//Fuction for setting PIC masks
void pic_set_mask(uint8_t mask1, uint8_t mask2);

//Function for acknowledging an interrupt
void pic_ack_interrupt(uint8_t int_num);

#endif