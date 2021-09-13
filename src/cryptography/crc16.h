/**
 * \file crc16.h
 *
 * \brief Header file of the CRC16-CCITT module.
 */
#ifndef CRC16_H
#define CRC16_H
#include <core/core.h>

// Calculate the CRC16-CCITT of the given message.
u16 crc16_calculate(const u8* msg, usize length);

#endif
