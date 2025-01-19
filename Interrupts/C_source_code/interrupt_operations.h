#ifndef INTERRUPT_OPERATIONS_H
#define INTERRUPT_OPERATIONS_H

//Function for checking whether interrupts are turned on
int ints_set();

//Function for enabling interrupts
void enable_ints();

//Function for disabling interrupts
void disable_ints();

#endif