#pragma once

#include "Core/Core.h"

class MMU {
public:
    MMU();
    virtual ~MMU();

    // Fill length number of bytes.
    static void Fill(u8 *base, u8 value, isize length);
};
