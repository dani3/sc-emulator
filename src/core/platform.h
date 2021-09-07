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

// Initialize the system so that it mimics the real device as closely as possible.
void platform_create(void);
// Free resources and cleanup.
void platform_destroy(void);

#endif
