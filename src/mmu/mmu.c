/**
 * \file mmu.c
 *
 * \brief
 */
#include <mmu/mmu.h>

/**
 * \brief
 */
void mmu_init(void) {
}

/**
 * \brief
 *
 * \param base
 * \param value
 * \param length
 */
void mmu_fill(u8* base, u8 value, isize length) {
  // TODO Write word wise when possible.
  for (int i = 0; i < length; ++i) {
    base[i] = value;
    base++;
  }
}
