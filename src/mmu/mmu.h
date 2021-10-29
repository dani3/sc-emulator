/**
 * \file mmu.h
 *
 * \brief
 */
#ifndef MMU_H
#define MMU_H
#include <core/core.h>

// Initialize the Memory Management Unit.
void mmu_init(void);
// Fill length number of bytes.
void mmu_fill(u8* base, u8 value, isize length);

#endif
