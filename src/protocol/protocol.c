/** \file protocol.h
 * \brief module that encapsulates the communication protocol.
 */
#include <core/core.h>
#include <core/logger.h>
#include <protocol/protocol.h>
#include <protocol/t0.h>

/** \fn void protocol_startup(void)
 * \brief initializes the protocol.
 *
 * \return Void.
 */
void protocol_startup(void) {
    io_init();

    send_atr();
}
