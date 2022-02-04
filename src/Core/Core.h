/**
 * \file Core.h
 *
 * \brief Main header file that most of the files should include.
 */
#pragma once

// Types definition.
#include "Core/Types.h"
// Logger module.
#include "Core/Log.h"
// Result type.
#include "Core/Result.h"
// Needed to raise a SIGTRAP.
#include <signal.h>
// For having access to smart pointers.
#include <memory>

// * ==============================================================================================
// * ASSERTS
// * ==============================================================================================

#define SC_ASSERT(x, ...)                                                                          \
    {                                                                                              \
        if (!(x)) {                                                                                \
            SC_ERROR("Assertion failed: {0}", __VA_ARGS__);                                        \
            raise(SIGTRAP);                                                                        \
        }                                                                                          \
    }

// * ==============================================================================================
// * Simulator version (following semantic versioning)
// * ==============================================================================================

// Major digit of the version of the emulator.
#define SC_VERSION_MAJOR 0
// Minor digit of the version of the emulator.
#define SC_VERSION_MINOR 0
// Patch digit of the version of the emulator.
#define SC_VERSION_PATCH 0
