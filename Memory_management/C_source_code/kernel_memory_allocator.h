#ifndef KERNEL_MEMORY_ALLOCATOR_H
#define KERNEL_MEMORY_ALLOCATOR_H

#define INVALID_HEAP_END_VALUE 0x1
#define HEAP_OUT_OF_MEMORY     0x2
#define INVALID_FREE_ADDRESS   0x3

//Initialize kernel heap
int init_kernel_memory_allocator(uint32_t heap_start, uint32_t heap_end, uint32_t* pd_addr, uint32_t last_pf_num);

//Kernel memory allocation
void* kmalloc(int bytes);

//Kernel memory deallocation
int kfree(void* ptr);

#endif