/** \file main.c
 * \brief entry point of the emulator.
 *
 */
#include <core/logger.h>
#include <protocol/protocol.h>

int main() {
    log_info("starting sc-emulator");
    // Initialize the protocol.
    protocol_startup();

    // Send/receive loop
    while (1) {

    }

    return 0;
}
