/**
 * \file platform.h
 *
 * \brief Implementation of the platform that can emulate a real device.
 */
#include <core/core.h>

#include <sys/mman.h>

#define RAM_SIZE 0x10000 ///< Size of the RAM area.
#define NVM_SIZE 0x52000 ///< Size of the NVM area.

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
