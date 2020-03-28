#include "unity.h"

#include "atr.h"

void setUp(void) {}

void tearDown(void) {}

void test_get_atr_correct(void)
{
    u8 atr_expected[] = {
        0x3B, 0x78, 0x96, 0x00, 0x00, 0x53, 0x43, 0x06, 0x60, 0x01, 0x07, 0x90, 0x00
    };

    TEST_ASSERT_EQUAL_HEX8_ARRAY(atr_expected, get_atr(), sizeof(atr_expected) / sizeof(u8));
}
