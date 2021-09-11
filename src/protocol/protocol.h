/**
 * \file protocol.h
 *
 * \brief Header file of the protocol component. This file provides a platform-agnostic API to
 * receive APDUs and send the response.
 *
 * This module is initialized by calling \ref protocol_init. Once initialized, the rest of the API
 * can be safely used.
 */
#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <core/core.h>

/**
 * \brief Struct that represents a c_apdu and r_apdu as defined in the ISO_7816-3/4.
 */
typedef struct {
  u8 cla;       ///< Class byte.
  u8 ins;       ///< Instruction byte.
  u8 p1;        ///< P1 byte.
  u8 p2;        ///< P2 byte.
  u8 p3;        ///< P3 byte.
  u8 data[256]; ///< Data buffer.
  u16 nc;       ///< Number of bytes received.
  u16 ne;       ///< Expected data.
  u16 nr;       ///< Number of bytes to be sent.
  u8 sw1;       ///< First byte of the status word.
  u8 sw2;       ///< Second byte of the status word.
} apdu_t;

// Initialize the protocol and send the ATR.
void protocol_init(void);
// Receive a command APDU.
apdu_t* protocol_receive(void);
// Send the data and/or the SW.
void protocol_send(const apdu_t* r_apdu);
// Helper function to set the status word given a u16.
void protocol_set_sw(u16 sw, apdu_t* apdu);
// Return a mutable pointer to the apdu_t struct.
apdu_t* protocol_get_apdu_as_mut_ptr(void);

#endif
