#ifndef PIC_SETUP_H
#define PIC_SETUP_H

#include "stdint.h"

//Macros for PIC remapping
#define PIC1_INT_OFFSET  0x20       //New PIC1 interrupt offset
#define PIC2_INT_OFFSET  0x28       //New PIC2 interrupt offset

void pic_remap(uint8_t offset1, uint8_t offset2);

uint8_t pic1_get_mask();

uint8_t pic2_get_mask();

void pic1_set_mask(uint8_t mask);

void pic2_set_mask(uint8_t mask);

void pic_ack_interrupt(uint8_t int_num);

#endif