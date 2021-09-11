/**
 * \file protocol.c
 *
 * \brief Implementation of the protocol module.
 */
#include <core/checkpoint.h>
#include <protocol/atr.h>
#include <protocol/protocol.h>
#include <protocol/tcpip_server.h>

#include <stdlib.h>
#include <string.h>

#define CONTROL_COLD_RESET 0
#define CONTROL_TRANSMIT   1
#define CONTROL_EXIT       2

#define HEADER_SIZE 5

/**
 * \brief Struct that represents a packet receiced from the external world.
 *
 * The `control` byte is mandatory. The rest are optional.
 */
typedef struct {
  u8 control;   ///< Control byte. Used to determine the type of information that follows (if any).
  u16 length;   ///< Length of the data (zero if no data).
  u8 data[258]; ///< Data buffer (256 bytes + SW).
} packet_t;

// APDU struct.
static apdu_t s_apdu;
// Packet struct received via TCP/IP.
static packet_t s_packet;

/**
 * \brief Initialize the protocol and send the ATR.
 */
void protocol_init(void) {
  log_info("initializing protocol...");

  usize atr_length;
  const u8* atr = get_atr(&atr_length);

  memcpy(s_packet.data, atr, atr_length);
  s_packet.length = atr_length;

  print_atr();

  server_send((const u8*) &s_packet.length, sizeof(s_packet.length));
  server_send(s_packet.data, s_packet.length);
}

/**
 * \brief Receive a command APDU. This function will not retry. If an error occurs the connection is
 * closed.
 *
 * The apdu_t is always cleared before receiving the command, i.e. any data from the previous
 * command is erased.
 *
 * \note This function is blocking.
 *
 * \return Pointer to an apdu_t struct.
 */
apdu_t* protocol_receive(void) {
  log_info("waiting for a new command...");

  // Clear the struct.
  memset((u8*) &s_apdu, 0, sizeof(s_apdu));

  // Receive the control byte.
  if (server_recv((u8*) &s_packet.control, sizeof(s_packet.control))) {
    longjmp(g_reset_checkpoint, ACCEPT_NEW_CONNECTION);
  }

  switch (s_packet.control) {
    case CONTROL_COLD_RESET:
      longjmp(g_reset_checkpoint, COLD_RESET);
      break;

    case CONTROL_EXIT:
      longjmp(g_reset_checkpoint, EXIT);
      break;
  }

  // Receive the length.
  if (server_recv((u8*) &s_packet.length, sizeof(s_packet.length))) {
    longjmp(g_reset_checkpoint, ACCEPT_NEW_CONNECTION);
  }

  if (s_packet.length) {
    if (server_recv((u8*) &s_apdu, s_packet.length)) {
      longjmp(g_reset_checkpoint, ACCEPT_NEW_CONNECTION);
    }
  }

  log_info(
      "apdu received: %02X %02X %02X %02X %02X", s_apdu.cla, s_apdu.ins, s_apdu.p1, s_apdu.p2,
      s_apdu.p3);

  // If it's a 4-byte case 1 command.
  if (s_packet.length == 4) {
    s_packet.length++;
  }

  if ((s_apdu.p3 + HEADER_SIZE) == s_packet.length) {
    // Case 1
    // Case 2
    // Case 3 with p3 == 0
    // Case 4 with no Le
    s_apdu.ne = s_apdu.p3;
    s_apdu.nc = 0;

  } else if (((s_apdu.p3 + HEADER_SIZE) > s_packet.length) && (s_packet.length == HEADER_SIZE)) {
    // Case 3 with p3 <> 0
    s_apdu.ne = s_apdu.p3;
    s_apdu.nc = 0;

  } else if ((s_apdu.p3 + HEADER_SIZE + 1) == s_packet.length) {
    // Case 4 command and Le is present.
    s_apdu.ne = s_apdu.data[s_apdu.p3];
    s_apdu.nc = s_apdu.p3;
  }

  return &s_apdu;
}

/**
 * \brief Send the data and/or the SW. This function expects that at least apdu_t.nr, apdu_t.sw1 and
 * apdu_t.sw2 are set.
 *
 * \param apdu Pointer to the apdu to be sent.
 */
void protocol_send(const apdu_t* apdu) {
  log_info("sending response...");

  if (apdu->nr > 0) {
    memcpy(s_packet.data, apdu->data, apdu->nr);

    s_packet.length = apdu->nr + 2;
    s_packet.data[apdu->nr] = apdu->sw1;
    s_packet.data[apdu->nr + 1] = apdu->sw2;
  } else {
    s_packet.length = 2;
    s_packet.data[0] = apdu->sw1;
    s_packet.data[1] = apdu->sw2;
  }

  server_send((const u8*) &s_packet.length, sizeof(s_packet.length));
  server_send(s_packet.data, s_packet.length);
}

/**
 * \brief Return a mutable pointer to the apdu_t struct.
 *
 * \return mutable pointer to an apdu_t struct.
 */
apdu_t* protocol_get_apdu_as_mut_ptr(void) {
  return &s_apdu;
}

/**
 * \brief Helper function to set the status word given a u16.
 *
 * \param sw status word to be set.
 * \param apdu pointer to an apdu_t struct.
 */
void protocol_set_sw(u16 sw, apdu_t* apdu) {
  apdu->sw1 = (u8) (sw >> 8);
  apdu->sw2 = (u8) (sw & 0xFF);
}
