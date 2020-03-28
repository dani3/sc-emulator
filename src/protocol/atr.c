/** \fn atr.c
 *\brief module that manages the ATR.
 */
#include <core/core.h>
#include <protocol/atr.h>

const u8 COLD_OPERATIONAL_ATR[] = {
    0x3B, 0x78, 0x96, 0x00, 0x00, 0x53, 0x43, 0x06, 0x60, 0x01, 0x07, 0x90, 0x00
};

u8* get_atr(void) {
    return (u8 *)COLD_OPERATIONAL_ATR;
}
