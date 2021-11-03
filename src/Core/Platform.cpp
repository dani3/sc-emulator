/**
 * \file platform.c
 *
 * \brief Implementation of the platform that can emulate a real device.
 */
#include <core/core.h>
#include <sys/mman.h>

// Pointer to the start of the RAM area.
static u8* s_ram_start;
// Pointer to the start of the NVM area.
static u8* s_nvm_start;

/**
 * \brief
 */
void platform_create(void) {
  s_ram_start = mmap(NULL, RAM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0);
  s_nvm_start = mmap(NULL, NVM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0);
}

/**
 * \brief
 */
void platform_destroy(void) {
  /// \todo Free RAM and NVM areas.
}

/**
 * \brief Return an immutable pointer to the start of the RAM.
 *
 * \return Constant pointer to the start of the RAM.
 */
const u8* get_ram_start(void) {
  return (const u8*) s_ram_start;
}

/**
 * \brief Return a mutable pointer to the start of the RAM.
 *
 * \return Mutable pointer to the start of the RAM.
 */
u8* get_ram_start_as_mut(void) {
  return s_ram_start;
}

/**
 * \brief Return an immutable pointer to the start of the NVM.
 *
 * \return Constant pointer to the start of the NVM.
 */
const u8* get_nvm_start(void) {
  return (const u8*) s_nvm_start;
}

/**
 * \brief Return a mutable pointer to the start of the NVM.
 *
 * \return Mutable pointer to the start of the NVM.
 */
u8* get_nvm_start_as_mut(void) {
  return s_nvm_start;
}
