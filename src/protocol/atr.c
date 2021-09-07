/**
 * \file atr.c
 *
 * \brief Implementation of the ATR module.
 */
#include <protocol/atr.h>

#include <string.h>

const u8 ATR[] = { 0x3B, 0x78, 0x96, 0x00, 0x00, 0x53, 0x43, 0x06, 0x60, 0x01, 0x07, 0x90, 0x00 };

/**
 * \brief Return an immutable pointer to the ATR.
 *
 * \param length [OUT] length of the ATR.
 *
 * \return const pointer to the ATR.
 */
const u8* get_atr(usize* length) {
  *length = sizeof(ATR);
  return ATR;
}

/**
 * \brief Print an ASCII representation of the ATR.
 */
void print_atr(void) {
  char string[255] = { [0 ... 254] = 0 };
  for (usize i = 0; i < sizeof(ATR); i++) {
    snprintf(&string[strlen(string)], sizeof(ATR), "%02X ", ATR[i]);
  }

  log_info("sending ATR... %s", string);
}
