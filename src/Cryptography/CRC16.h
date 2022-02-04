#pragma once

#include "Core/Core.h"

/**
 * \brief Class that implements the CRC16-CCITT algorithm.
 */
class CRC16 {
public:
    // Calculate the CRC16-CCITT of the given message.
    static u16 Calculate(const u8 *msg, usize length);
};
