/**
 * \file atr.h
 *
 * \brief Header file that defines everything related to the ATR.
 */
#ifndef ATR_H
#define ATR_H
#include <core/core.h>

// Return an immutable pointer to the ATR.
const u8* get_atr(usize* length);
// Print an ASCII representation of the ATR.
void print_atr(void);

#endif
