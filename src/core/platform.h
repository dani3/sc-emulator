/**
 * \file platform.h
 *
 * \brief Header file that defines the platform.
 *
 * It initializes the system so that it mimics as much as possible the final target, e.g. creates
 * the memory regions that represent the EEPROM and RAM.
 */
#ifndef PLATFORM_H
#define PLATFORM_H

// Types definition.
#include <core/types.h>

#define RAM_SIZE 0x10000 ///< Size of the RAM area.
#define NVM_SIZE 0x52000 ///< Size of the NVM area.

// Initialize the system so that it mimics the real device as closely as possible.
void platform_create(void);
// Free resources and cleanup.
void platform_destroy(void);

// Return an immutable pointer to the start of the RAM.
const u8* get_ram_start(void);
// Return a mutable pointer to the start of the RAM.
u8* get_ram_start_as_mut(void);
// Return an immutable pointer to the start of the NVM.
const u8* get_nvm_start(void);
// Return a mutable pointer to the start of the NVM.
u8* get_nvm_start_as_mut(void);

// Align a variable to the given size boundary.
#define ALIGN(x) __attribute__((aligned(x)))
// Place the variable in a given section.
#define AT(s) __attribute__((section(s)))
// Suggest the compiler to inline the function.
#define FORCE_INLINE __attribute__((always_inline)) inline

#endif
