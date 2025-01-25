#ifndef PF_ALLOCATOR_H
#define PF_ALLOCATOR_H

#include "paging.h"
#include "stdint.h"

#define PAGE_MAPPING_FAILED 0x1

//Map a specified virtual page in the specified address space to a random physical frame
int map_page(uint32_t* pdt, uint32_t page_num, uint32_t r_w, uint32_t u_s, uint32_t pinned, uint32_t global);

//Map a specified virtual page in the specified address space to a specific physical frame
int map_page_to_pf(uint32_t* pdt, uint32_t page_num, uint32_t pf_num, uint32_t r_w, uint32_t u_s, uint32_t pinned, uint32_t global);

#endif