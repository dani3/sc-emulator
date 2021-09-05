/**
 * \file protocol.h
 *
 * \brief
 */
#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <core/core.h>

// Initialize the IO interface.
void protocol_init(void);
// Receive `length` bytes and stores them into `buf`.
void protocol_receive(u8* buf, usize length);
// Send `length` bytes stored at `buf`.
void protocol_send(const u8* buf, usize length);

#endif // #ifdef PROTOCOL_H
