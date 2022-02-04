#include "Memory/MMU.h"

MMU::MMU() {
}

MMU::~MMU() {
}

/**
 * \brief
 *
 * \param base
 * \param value
 * \param length
 */
void MMU::Fill(u8 *base, u8 value, isize length) {
    //    usize head = (usize) base & 0x03;
    //
    //    switch (head) {
    //    case 3:
    //        if (length) {
    //            *base = value;
    //            base++;
    //            length--;
    //        }
    //    case 2:
    //        if (length) {
    //            *base = value;
    //            base++;
    //            length--;
    //        }
    //    case 1:
    //        if (length) {
    //            *base = value;
    //            base++;
    //            length--;
    //        }
    //        break;
    //
    //    default:
    //        break;
    //    }
    //
    //    usize v = (usize) (value << 24 | value << 16 | value << 8 | value);
    //    for (usize i = 0; i < length / sizeof(usize); ++i) {
    //        *((usize *) base) = v;
    //        base += sizeof(usize);
    //    }

    // TODO Write word wise when possible.
    for (int i = 0; i < length; ++i) {
        base[i] = value;
        base++;
    }
}
