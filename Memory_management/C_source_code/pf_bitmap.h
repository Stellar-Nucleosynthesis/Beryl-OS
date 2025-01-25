#ifndef PF_ALLOCATION_H
#define PF_ALLOCATION_H

#include "stdint.h"

#define INVALID_PF_RANGE 0x1

//Initialize the range of accessible physical frames
int init_pf_bitmap(uint32_t min_pf, uint32_t max_pf);

//Mark a physical frame as used
void pf_mark_as_used(uint32_t pf);

//Mark a physical frame as unused
void pf_mark_as_free(uint32_t pf);

//Check if a physical frame is free
int pf_is_free(uint32_t pf);

//Mark all the frames in this range as used
void set_used_pfs(uint32_t min_pf, uint32_t max_pf);

//Get the number of the first available physical frame
uint32_t get_min_pf();

//Get the number of the last available physical frame
uint32_t get_max_pf();

#endif