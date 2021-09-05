/**
 * \file core.h
 *
 * \brief Main header file that most of the files should include.
 *
 * This file basically serves as a wrapper around all the main files that make up the project.
 */
#ifndef CORE_H
#define CORE_H

// Standard library.
#include <stdlib.h>
// Logger module.
#include <core/logger.h>
// Definition of the platform.
#include <core/platform.h>

// * ==============================================================================================
// * Emulator version (following semantic versioning)
// * ==============================================================================================

/// \brief Major digit of the version of the emulator.
#define SC_VERSION_MAJOR 0
/// \brief Minor digit of the version of the emulator.
#define SC_VERSION_MINOR 0
/// \brief Patch digit of the version of the emulator.
#define SC_VERSION_PATCH 0

// * ==============================================================================================
// * ASSERTS
// * ==============================================================================================

#define SC_ASSERT(x, ...)                                                                          \
  {                                                                                                \
    if (!(x)) {                                                                                    \
      log_error("assertion failed: %s", __VA_ARGS__);                                              \
      exit(-1);                                                                                    \
    }                                                                                              \
  }

#endif
