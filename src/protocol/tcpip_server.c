/** \file tcpip_server.c
 *
 * \brief Implementation of a TCP/IP server module.
 *
 * This server communicates with targets where the form of communication is many sequential
 * request/response, request/response, request/response (c_apdu/r_apdu) messages back and forth. In
 * this scenario, the payloads are often length-value encoded, and the length and value may be two
 * separates writes to the socket. This is the dreaded write-write-read (see reference below)
 * sequence that leads to unwanted delays when Nagle's algorithm and TCP delayed ACK are both
 * enabled. Therefore, Nagle's algorithm is disable to prevent a bad interaction with TCP delayed
 * ACK.
 *
 * \ref https://en.wikipedia.org/wiki/Nagle%27s_algorithm#Interaction_with_delayed_ACK
 */
#include <protocol/tcpip_server.h>

#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>

#define DEFAULT_PORT 8080

// Socket used ot listen for new connections.
static int s_listen_socket;
// Client socket used for communicating with an accepted connection.
static int s_client_socket;

/**
 * \brief Initialize a TCP/IP server Upon calling a new connection can be accepted.
 */
void server_init(void) {
  struct sockaddr_in remote;

  log_debug("initializing TCP/IP server at port %i...", DEFAULT_PORT);

  // Create the socket.
  s_listen_socket = socket(AF_INET, SOCK_STREAM, 0);
  SC_ASSERT(s_listen_socket >= 0, "failed to create socket...");

  usize on = 1;
  SC_ASSERT(
      setsockopt(s_listen_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == 0,
      "error while setting socket option...");

  // Disable Nagle's algorithm (see file header).
  SC_ASSERT(
      setsockopt(s_listen_socket, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on)) == 0,
      "error while setting socket option...");

  remote.sin_family = AF_INET;
  remote.sin_addr.s_addr = htonl(INADDR_ANY);
  remote.sin_port = htons(DEFAULT_PORT);

  // Set up the TCP listening socket.
  SC_ASSERT(
      bind(s_listen_socket, (struct sockaddr*) &remote, sizeof(remote)) >= 0,
      "failed to bind socket...");

  SC_ASSERT(listen(s_listen_socket, 1) >= 0, "unable to set socket backlog...");
}

/**
 * \brief Wait until a new connection arrives.
 *
 * \note This is a blocking method.
 */
void server_accept(void) {
  struct sockaddr_in client;
  socklen_t client_size = sizeof(client);

  log_debug("listening for connections...");
  s_client_socket = accept(s_listen_socket, (struct sockaddr*) &client, &client_size);
  SC_ASSERT(s_client_socket >= 0, "failed to accept connection...")
  log_debug("new connection accepted...");
}

/**
 * \brief receives `length` bytes and stores them into `buf`.
 *
 * \param buf: buffer to store the data.
 * \param length: length of the data.
 *
 * \return 0 if the reception succeded, -1 if an error occured, -2 if the connection has been
 * closed.
 */
server_result_t server_recv(u8* buf, usize length) {
  int result = recv(s_client_socket, buf, length, 0);
  if (result > 0) {
    // If the reception is succesful, `recv` returns the number of bytes received.
    return OK;

  } else if (result == 0) {
    // If `recv` returns zero it means that the connection has been closed.
    return CONNECTION_CLOSED;

  } else {
    // If it returns something else, an error occured.
    return FATAL_ERROR;
  }
}

/**
 * \brief sends `length` bytes stored at `data`.
 *
 * \param data: data to be transmitted.
 * \param length: length of the data.
 */
void server_send(const u8* data, usize length) {
  SC_ASSERT(send(s_client_socket, data, length, 0) >= 0, "failed to transmit...");
}

/**
 * \brief Close the TCP/IP server.
 */
void server_close(void) {
  SC_ASSERT(close(s_client_socket) >= 0, "failed to close server...");
}
