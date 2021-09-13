/**
 * \file test_crc16.c
 *
 * \brief CRC16 unit tests.
 */
//! @cond

#include "unity.h"

#include <string.h>

#include "crc16.h"

void setUp(void) {
}

void tearDown(void) {
}

//! @endcond

/**
 * \brief Test that the CRC16 is calculated for a 1-byte message.
 */
void test_crc16_1_byte(void) {
  u8 msg[1];

  msg[0] = 0x01;
  TEST_ASSERT_EQUAL_HEX16(0x1021, crc16_calculate(msg, sizeof(msg)));

  msg[0] = 0xA5;
  TEST_ASSERT_EQUAL_HEX16(0xE54F, crc16_calculate(msg, sizeof(msg)));
}

/**
 * \brief Test that the CRC16 is calculated for a 2-byte message.
 */
void test_crc16_2_bytes(void) {
  u8 msg[2];

  msg[0] = 0x01;
  msg[1] = 0x01;
  TEST_ASSERT_EQUAL_HEX16(0x2310, crc16_calculate(msg, sizeof(msg)));

  msg[0] = 0xA5;
  msg[1] = 0xA5;
  TEST_ASSERT_EQUAL_HEX16(0x07C4, crc16_calculate(msg, sizeof(msg)));
}

/**
 * \brief Test that the CRC16 is calculated for an 8-byte message.
 */
void test_crc16_8_bytes(void) {
  u8 msg[8];

  memset(msg, 0x01, sizeof(msg));
  TEST_ASSERT_EQUAL_HEX16(0x72D7, crc16_calculate(msg, sizeof(msg)));

  memset(msg, 0xA5, sizeof(msg));
  TEST_ASSERT_EQUAL_HEX16(0xDE7E, crc16_calculate(msg, sizeof(msg)));
}

/**
 * \brief Test that the CRC16 is calculated for a 256-byte message.
 */
void test_crc16_256_bytes(void) {
  u8 msg[256];

  memset(msg, 0x01, sizeof(msg));
  TEST_ASSERT_EQUAL_HEX16(0xD034, crc16_calculate(msg, sizeof(msg)));

  memset(msg, 0xA5, sizeof(msg));
  TEST_ASSERT_EQUAL_HEX16(0xE2D2, crc16_calculate(msg, sizeof(msg)));
}
