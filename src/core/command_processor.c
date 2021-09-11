/**
 * \file command_processor.c
 *
 * \brief
 */
#include <core/command_processor.h>
#include <core/core.h>
#include <protocol/protocol.h>

/**
 * \brief
 */
void process_commands(void) {
  apdu_t* apdu;

  while (true) {
    apdu = protocol_receive();

    apdu->sw1 = 0x90;
    apdu->sw2 = 0x00;

    protocol_send(apdu);
  }
}
