#pragma once

#include "Core/Core.h"

/**
 * \brief Collection of all the status words the system can reply.
 */
class StatusWords {
public:
    static const u16 OK = 0x9000;

    static const u16 UNKNOWN_INS = 0x7D00;   ///< Unknown class.
    static const u16 UNKNOWN_CLASS = 0x7E00; ///< Unknown class.
    static const u16 WRONG_STATE = 0x7FFF;   ///< Card in wrong state.
};
