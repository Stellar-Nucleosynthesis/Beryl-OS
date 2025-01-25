#include "stdint.h"
#include "pf_bitmap.h"

#define BITMAP_SIZE 0x100000

uint8_t bitmap[BITMAP_SIZE];

uint32_t min_available_pf;
uint32_t max_available_pf;

int init_pf_bitmap(uint32_t min_pf, uint32_t max_pf)
{
	if (min_pf > max_pf) return INVALID_PF_RANGE;
	for (int i = 0; i < BITMAP_SIZE; ++i)
	{
		bitmap[i] = 0;
	}
	min_available_pf = min_pf & 0xFFFFF;
	max_available_pf = max_pf & 0xFFFFF;
	return 0;
}

void pf_mark_as_used(uint32_t pf)
{
	if (pf > max_available_pf || pf < min_available_pf) return;
	uint8_t bit = 0x80;
	for (uint32_t i = 0; i < (pf & 0x7); ++i)
	{
		bit /= 2;
	}
	bitmap[pf >> 3] |= bit;

}

void pf_mark_as_free(uint32_t pf)
{
	if (pf > max_available_pf || pf < min_available_pf) return;
	uint8_t bit = 0x80;
	for (uint32_t i = 0; i < (pf & 0x7); ++i)
	{
		bit /= 2;
	}
	uint8_t mask = 0xFF ^ bit;
	bitmap[pf >> 3] &= mask;
}

int pf_is_free(uint32_t pf)
{
	if (pf > max_available_pf || pf < min_available_pf) return 0;
	uint8_t byte = bitmap[pf >> 3];
	byte = 0x1 & (byte >> (7 - (pf & 0x7)));
	return !byte;
}

void set_used_pfs(uint32_t min_pf, uint32_t max_pf)
{
	if (min_pf > max_pf) return;
	if (min_pf < min_available_pf) min_pf = min_available_pf;
	if (max_pf > max_available_pf) max_pf = max_available_pf;

	for (uint32_t pf = min_pf; pf <= max_pf; ++pf)
	{
		pf_mark_as_used(pf);
	}
}

uint32_t get_min_pf()
{
	return min_available_pf;
}

uint32_t get_max_pf()
{
	return max_available_pf;
}