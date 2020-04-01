/** \file protocol.c
 * \brief module that encapsulates the communication protocol.
 */
#include <core/core.h>
#include <core/logger.h>
#include <protocol/protocol.h>
#include <protocol/protocol_data.h>
#ifdef T0_PROTOCOL
#  include <protocol/t0.h>
#endif

u8 io_buffer[IO_BUFFER_SIZE] = { 0 };
u16 sw = 0;

/** \fn protocol_startup
 * \brief initializes the protocol.
 *
 * \return Void.
 */
void protocol_startup(void) {
  io_init();

#ifdef T0_PROTOCOL
  send_atr();
#endif
}
