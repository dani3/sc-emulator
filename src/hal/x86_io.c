/** \file x86_io.c
 * \brief I/O module of the emulator.
 *
 */
#include <core/core.h>
#include <core/logger.h>

#include <protocol/protocol_data.h>

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT    8080

typedef struct {
	u32 socket;
	u32 socket_desc;
} server_t;

static server_t server;

/** \fn u16 create_socket(void)
 * \brief creates a socket for the server and makes it passive such that
 * we can wait for connections on it later.
 *
 * \return socket descriptor if success, negative number otherwise.
 */
static u16 create_socket(void) {
	log_debug("create socket...");

	server.socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	return server.socket_desc;
}

/** \fn u32 bind_socket(u16 socket)
 * \brief binds the created socket to a specific port.
 *
 * \return zero if success, negative number otherwise.
 */
static u32 bind_socket(void) {
	struct sockaddr_in remote = { 0 };

	remote.sin_family = AF_INET;
	remote.sin_addr.s_addr = htonl(INADDR_ANY);
	remote.sin_port = htons(PORT);

	log_debug("bind socket...");
	return bind(server.socket_desc, (struct sockaddr *) &remote, sizeof(remote));
}

/** \fn u32 io_init(void)
 * \brief initializes I/O module.
 *
 * \return zero if success, negative number if an error occured.
 */
u8 io_init(void) {
	struct sockaddr_in client;
	u8 message[5];

	log_info("initializing i/o");

	// Create the socket
	if ((create_socket()) < 0) {
		log_fatal("failed to create socket");
		return -1;
	}

	// Bind it
	if (bind_socket() < 0) {
		log_fatal("failed to bind socket");
		return -1;
	}

	listen(server.socket_desc, 1);

	// Wait for the reset
	log_info("initialized");
	log_info("waiting for reset");
	if ((server.socket = accept(server.socket_desc, (struct sockaddr *) &client, (socklen_t *) sizeof(struct sockaddr_in)) < 0)) {
		log_fatal("failed to accept request");
		return -1;
	}

	if (recv(server.socket, message, 5, 0) < 0) {
		log_fatal("failed to receive reset");
		return -1;
	}

	log_info("reset received");

	return 0;
}

/** \fn u8 io_receive(u8* buf, u16 length)
 * \brief receives `length` bytes and stores them into `buf`.
 *
 * \param buf: buffer to store the data.
 * \param length: length of the data.
 *
 * \return zero if success, negative number otherwise.
 */
u8 io_receive(u8* buf, u16 length) {
	if (recv(server.socket, buf, length, 0) < 0) {
		log_fatal("failed to receive");
		return -1;
	}

	return 0;
}

/** \fn u8 io_receive(u8* data, u16 length)
 * \brief sends `length` bytes stored at `data`.
 *
 * \param data: data to be transmitted.
 * \param length: length of the data.
 *
 * \return zero if success, negative number otherwise.
 */
u8 io_send(u8* data, u16 length) {
	if (send(server.socket, data, length, 0) < 0) {
		log_fatal("failed to send");
		return -1;
	}

	return 0;
}
