#ifndef PAGING_H
#define PAGING_H

#include "stdint.h"

#define KERNEL_OFFSET 0xC0000000

typedef struct __attribute__((packed)) 
{
    uint32_t present : 1;          //Bit 0: Page present in memory
    uint32_t read_write : 1;       //Bit 1: Read (0) / Read-Write (1) permission
    uint32_t user_supervisor : 1;  //Bit 2: User (1) / Supervisor (0)
    uint32_t write_through : 1;    //Bit 3: Write-through enabled
    uint32_t cache_disable : 1;    //Bit 4: Caching disabled
    uint32_t accessed : 1;         //Bit 5: Page accessed
    uint32_t available1 : 1;       //Bit 6: Available for OS use
    uint32_t page_size : 1;        //Bit 7: Page size (0 = 4 KB, 1 = 4 MB)
    uint32_t available4 : 4;       //Bits 8�11: Available for OS use
    uint32_t pt_address : 20;      //Bits 12�31: Page table address (aligned to 4 KB)
} pde;

typedef struct __attribute__((packed))
{
    uint32_t present : 1;          // Bit 0: Page present in memory
    uint32_t read_write : 1;       // Bit 1: Read (0) / Read-Write (1) permission
    uint32_t user_supervisor : 1;  // Bit 2: Supervisor (0) / User (1) access
    uint32_t write_through : 1;    // Bit 3: Write-through caching (1 = enabled)
    uint32_t cache_disable : 1;    // Bit 4: Cache disabled (1 = no caching)
    uint32_t accessed : 1;         // Bit 5: Page accessed
    uint32_t dirty : 1;            // Bit 6: Page written to
    uint32_t page_size : 1;        // Bit 7: Page size (0 = 4 KB, 1 = 4 MB)
    uint32_t global : 1;           // Bit 8: Global page (not flushed from TLB)
    uint32_t available3 : 3;       // Bits 9�11: Available for OS use
    uint32_t pat : 1;              // Bit 12: Page Attribute Table
    uint32_t reserved : 9;         // Bits 13�21: Reserved (must be zero)
    uint32_t pf_address : 10;      // Bits 22�31: Physical frame address (aligned to 4 MB)
} pde_large;

typedef struct __attribute__((packed)) 
{
    uint32_t present : 1;          //Bit 0: Page present in memory
    uint32_t read_write : 1;       //Bit 1: Read (0) / Read-Write (1) permission
    uint32_t user_supervisor : 1;  //Bit 2: User (1) / Supervisor (0)
    uint32_t write_through : 1;    //Bit 3: Write-through enabled
    uint32_t cache_disable : 1;    //Bit 4: Cache disabled
    uint32_t accessed : 1;         //Bit 5: Page accessed
    uint32_t dirty : 1;            //Bit 6: Page written to
    uint32_t pat : 1;              //Bit 7: Page Attribute Table
    uint32_t global : 1;           //Bit 8: Global page (not flushed from TLB)
    uint32_t available3 : 3;       //Bits 9�11: Available for OS use
    uint32_t pf_address : 20;      //Bits 12�31: Physical frame address (aligned to 4 KB)
} pte;

void load_pd(uint32_t pd_addr);

void enable_paging();

void enable_large_pages();

void fill_pde(pde* pde_ptr, uint32_t pt_addr, uint32_t pcd, uint32_t pwt, uint32_t u_s, uint32_t rw, uint32_t p);

void fill_pde_large(pde_large* pde_ptr, uint32_t pf_addr, uint32_t pat, uint32_t g, uint32_t pcd, uint32_t pwt, uint32_t u_s, uint32_t rw, uint32_t p);

void fill_pte(pte* pte_ptr, uint32_t pf_addr, uint32_t g, uint32_t pat, uint32_t pcd, uint32_t pwt, uint32_t u_s, uint32_t rw, uint32_t p);

uint32_t get_phys_addr(uint32_t addr);

#endif
