#include "stdint.h"
#include "pf_allocator.h"
#include "kernel_memory_allocator.h"

#define MAGIC_NUM1 0xC001
#define MAGIC_NUM2 0xB0A2

uint32_t kernel_heap_start;
uint32_t kernel_heap_end;             //Always the last byte of a page

uint32_t* kernel_pd_addr;
uint32_t last_kernel_pf_num;

struct free_space 
{
	struct free_space* next_free_space;
	uint32_t size;
} __attribute__((packed));

struct alloc_header
{
	uint16_t magic1;
	uint32_t size;
	uint16_t magic2;
} __attribute__((packed));

struct free_space* head;

int allocate_new_page() 
{
	uint32_t entry_num = (kernel_heap_end / 0x1000) + 1;
	int res = map_page_to_pf(kernel_pd_addr, entry_num, last_kernel_pf_num + 1, 1, 0, 1, 0);
	if (res != 0)
	{
		return HEAP_OUT_OF_MEMORY;
	}
	last_kernel_pf_num++;
	kernel_heap_end += 0x1000;
	return 0;
}

int init_kernel_memory_allocator(uint32_t heap_start, uint32_t heap_end, uint32_t* pd_addr, uint32_t last_pf_num)
{
	kernel_heap_start = heap_start;
	if (heap_end % 0x1000 != 0xFFF) return INVALID_HEAP_END_VALUE;
	kernel_heap_end = heap_end;
	kernel_pd_addr = pd_addr;
	last_kernel_pf_num = last_pf_num;
	if (kernel_heap_end - kernel_heap_start < 4095)
	{
		int res = allocate_new_page();
		if (res != 0) 
		{
			return HEAP_OUT_OF_MEMORY;
		}
	}
	struct free_space* start_free_space = (struct free_space*)kernel_heap_start;
	start_free_space->next_free_space = NULL;
	start_free_space->size = (heap_end - heap_start + 1) - sizeof(struct free_space);
	head = start_free_space;
	return 0;
}

void* kmalloc(int bytes) 
{
	if (bytes < 0) return NULL;
	struct free_space* curr = head;
	struct free_space* prev = NULL;
	while (1) 
	{
		if (curr->size >= bytes + sizeof(struct alloc_header))
		{
			uint32_t size = curr->size;
			struct free_space* next = curr->next_free_space;
			uint8_t* zeroing_ptr = (uint8_t*)curr;
			void* result = zeroing_ptr + sizeof(struct alloc_header);
			for (uint32_t i = 0; i < bytes + sizeof(struct alloc_header); ++i)
			{
				*zeroing_ptr++ = 0;
			}
			struct alloc_header* alloc_header = (struct alloc_header*)curr;
			alloc_header->size = bytes;
			alloc_header->magic1 = MAGIC_NUM1;
			alloc_header->magic2 = MAGIC_NUM2;
			struct free_space* new_free_space = (struct free_space*)(zeroing_ptr);
			new_free_space->size = size - bytes - sizeof(struct alloc_header);
			new_free_space->next_free_space = head;
			if (prev != NULL) 
			{
				prev->next_free_space = next;
			}
			head = new_free_space;
			return result;
		}
		if (curr->next_free_space == NULL) 
		{
			break;
		}
		prev = curr;
		curr = curr->next_free_space;
	}
	uint32_t free_space_in_end = 0;
	for (uint32_t i = 0; i < bytes + sizeof(struct alloc_header) + sizeof(struct free_space); i += 0x1000)
	{
		int res = allocate_new_page();
		if (res != 0)
		{
			if (free_space_in_end > 0) 
			{
				struct free_space* free_header = (struct free_space*)(kernel_heap_end + 1);
				free_header->size = free_space_in_end - sizeof(struct free_space);
				free_header->next_free_space = NULL;
				curr->next_free_space = free_header;
				return NULL;
			}
			else
			{
				return NULL;
			}
		}
		free_space_in_end += 0x1000;
	}
	uint8_t* zeroing_ptr = (uint8_t*)(free_space_in_end + 1);
	void* result = zeroing_ptr + sizeof(struct alloc_header);
	for (uint32_t i = 0; i < bytes + sizeof(struct alloc_header); i++)
	{
		*zeroing_ptr++ = 0;
	}
	struct alloc_header* header = (struct alloc_header*)((free_space_in_end + 1));
	header->size = bytes;
	header->magic1 = MAGIC_NUM1;
	header->magic2 = MAGIC_NUM2;
	struct free_space* new_free_space = (struct free_space*)(zeroing_ptr);
	new_free_space->size = free_space_in_end - bytes - sizeof(struct alloc_header) - sizeof(struct free_space);
	new_free_space->next_free_space = NULL;
	curr->next_free_space = new_free_space;
	return result;
}

int kfree(void* ptr)
{
	if (ptr == NULL) 
	{
		return INVALID_FREE_ADDRESS;
	}
	uint8_t* byte_ptr = (uint8_t*)ptr;
	byte_ptr -= sizeof(struct alloc_header);
	struct alloc_header* alloc_header = (struct alloc_header*)byte_ptr;
	if (alloc_header->magic1 != MAGIC_NUM1 || alloc_header->magic2 != MAGIC_NUM2) 
	{
		return INVALID_FREE_ADDRESS;
	}
	uint32_t size = alloc_header->size;
	size = size + sizeof(struct alloc_header) - sizeof(struct free_space);
	struct free_space* new_free_space = (struct free_space*)byte_ptr;
	new_free_space->size = size;
	new_free_space->next_free_space = head;
	head = new_free_space;
	return 0;
}

