/**
 * \file Core.h
 *
 * \brief Main header file that most of the files should include.
 *
 * This file basically serves as a wrapper around all the main files that make up the project.
 */
#pragma once

// Logger module.
#include "Core/Log.h"
// Definition of the platform.
#include "Core/Platform.h"
// Project definiton.
#include "Core/Project.h"

// Standard library.
#include <stdlib.h>

// * ==============================================================================================
// * ASSERTS
// * ==============================================================================================

#define SC_ASSERT(x, ...)                                                                          \
  {                                                                                                \
    if (!(x)) {                                                                                    \
      SC_ERROR("Assertion failed: {0}", __VA_ARGS__);                                              \
      raise(SIGTRAP);                                                                              \
    }                                                                                              \
  }
