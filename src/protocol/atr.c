/** \file atr.c
 *\brief module that manages the ATR.
 */
#include <core/core.h>
#include <protocol/atr.h>

const u8 COLD_OPERATIONAL_ATR[] = {
  0x3B, 0x78, 0x96, 0x00, 0x00, 0x53, 0x43, 0x06, 0x60, 0x01, 0x07, 0x90, 0x00
};

/** \fn get_atr
 * \brief returns the ATR.
 *
 * \return the ATR.
 */
u8* get_atr(void) {
  return (u8 *)COLD_OPERATIONAL_ATR;
}

/** \fn get_atr_as_string
 * \brief returns a representation of the ATR.
 *
 * \return a representation of the ATR.
 */
u8* get_atr_as_string(void) {
  return "0x3B 0x78 0x96 0x00 0x00 0x53 0x43 0x06 0x60 0x01 0x07 0x90 0x00";
}
