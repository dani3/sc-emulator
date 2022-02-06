/**
 * \file atr.c
 *
 * \brief Implementation of the ATR module.
 */
#include "Protocol/Atr.h"

#include <string.h>

const u8 Atr::ATR[]
    = { 0x3B, 0x78, 0x96, 0x00, 0x00, 0x53, 0x43, 0x06, 0x60, 0x01, 0x07, 0x90, 0x00 };

Atr::Atr() {
}

Atr::~Atr() {
}

/**
 * \brief Return an immutable pointer to the ATR.
 *
 * \return const pointer to the ATR.
 */
const u8 *Atr::AsPtr() const {
    return Atr::ATR;
}

/**
 * \brief Return the size of the ATR.
 *
 * \return Size of the ATR.
 */
usize Atr::Size() const {
    return sizeof(ATR);
}

/**
 * \brief Print an ASCII representation of the ATR.
 */
void Atr::Print(void) const {
    char atr[255] = { 0 };
    for (usize i = 0; i < sizeof(ATR); i++) {
        snprintf(&atr[strlen(atr)], sizeof(ATR), "%02X ", ATR[i]);
    }

    SC_INFO("ATR: {0}", atr);
}
