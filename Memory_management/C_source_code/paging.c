#include "paging.h"
#include "stdint.h"

void fill_pde(struct pde* pde_ptr, uint32_t pt_addr, uint32_t pcd, uint32_t pwt, uint32_t u_s, uint32_t rw, uint32_t p) 
{
	pde_ptr->pt_address = pt_addr >> 12;
	pde_ptr->available4 = 0x0;
	pde_ptr->page_size = 0x0;
	pde_ptr->available1 = 0x0;
	pde_ptr->cache_disable = pcd & 0x1;
	pde_ptr->write_through = pwt & 0x1;
	pde_ptr->user_supervisor = u_s & 0x1;
	pde_ptr->read_write = rw & 0x1;
	pde_ptr->present = p & 0x1;
}

void fill_pde_large(struct pde_large* pde_ptr, uint32_t pf_addr, uint32_t pat, uint32_t g, uint32_t pcd, uint32_t pwt, uint32_t u_s, uint32_t rw, uint32_t p)
{
	pde_ptr->pf_address = pf_addr >> 22;
	pde_ptr->reserved = 0x0;
	pde_ptr->pat = pat & 0x1;
	pde_ptr->available3 = 0x0;
	pde_ptr->global = g & 0x1;
	pde_ptr->page_size = 0x1;
	pde_ptr->cache_disable = pcd & 0x1;
	pde_ptr->write_through = pwt & 0x1;
	pde_ptr->user_supervisor = u_s & 0x1;
	pde_ptr->read_write = rw & 0x1;
	pde_ptr->present = p & 0x1;
}

void fill_pte(struct pte* pte_ptr, uint32_t pf_addr, uint32_t g, uint32_t pat, uint32_t pcd, uint32_t pwt, uint32_t u_s, uint32_t rw, uint32_t p) 
{
	pte_ptr->pf_address = pf_addr >> 12;
	pte_ptr->available3 = 0x0;
	pte_ptr->global = g & 0x1;
	pte_ptr->pat = pat & 0x1;
	pte_ptr->cache_disable = pcd & 0x1;
	pte_ptr->write_through = pwt & 0x1;
	pte_ptr->user_supervisor = u_s & 0x1;
	pte_ptr->read_write = rw & 0x1;
	pte_ptr->present = p & 0x1;
}