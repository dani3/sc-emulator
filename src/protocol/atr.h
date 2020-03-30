/** \file atr.h
 *\brief module that manages the ATR.
 */
#ifndef ATR_H
#define ATR_H

#include <core/types.h>

#define ATR_LENGTH      13

/// \brief returns the ATR.
u8* get_atr(void);
/// \brief returns a representation of the ATR.
u8* get_atr_as_string(void);

#endif // #ifndef ATR_H
