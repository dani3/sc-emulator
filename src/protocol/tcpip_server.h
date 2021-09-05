/**
 * \file tcpip_server.h
 *
 * \brief Header file of the TCP/IP server.
 */
#include <core/core.h>

/**
 * \brief
 */
typedef enum {
  OK = 0,                 ///<
  FATAL_ERROR = -1,       ///<
  CONNECTION_CLOSED = -2, ///<
} server_result_t;

// Initialize the TCP/IP server.
void server_init(void);
// Wait until a new connection arrives.
void server_accept(void);
// Send a stream of bytes.
void server_send(const u8* data, usize length);
// Receive a stream of bytes.
server_result_t server_recv(u8* data, usize length);
// Close the TCP/IP server.
void server_close(void);
