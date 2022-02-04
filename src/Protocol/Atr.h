#pragma once

#include "Core/Core.h"

/**
 * \brief Class that represents the ATR (Answer to Reset) as defined in the ISO 7816-3
 */
class Atr {
public:
    Atr();
    virtual ~Atr();

    // Return an immutable pointer to the ATR.
    const u8 *AsPtr() const;

    // Return the size of the ATR.
    usize Size() const;

    // Print an ASCII representation of the ATR.
    void Print() const;

private:
    static const u8 ATR[];
};
