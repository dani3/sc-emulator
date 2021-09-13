/**
 * \file test_crc16.c
 *
 * \brief CRC16 unit tests.
 */
//! @cond

#include "unity.h"

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
