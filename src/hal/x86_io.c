/** \file x86_io.c
 * \brief
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

/** \fn u16 create_socket(void)
 * \brief creates a socket for the server and makes it passive such that
 * we can wait for connections on it later.
 *
 * \param
 *
 * \return
 */
static u16 create_socket(void) {
	log_debug("create socket...");
	return socket(AF_INET, SOCK_STREAM, 0);
}

/** \fn u32 bind_socket(u16 socket)
 * \brief binds the created socket to a specific port.
 *
 * \param
 *
 * \return
 */
static u32 bind_socket(u16 socket) {
	struct sockaddr_in remote = { 0 };

	remote.sin_family = AF_INET;
	remote.sin_addr.s_addr = htonl(INADDR_ANY);
	remote.sin_port = htons(PORT);

	log_debug("bind socket...");
	return bind(socket, (struct sockaddr *) &remote, sizeof(remote));
}

/** \fn u32 io_init(void)
 * \brief
 *
 * \return
 */
u32 io_init(void) {
	struct sockaddr_in client;
	u32 sock_desc;
	u32 sock;

	// Create the socket
	if ((sock_desc = create_socket()) < 0) {
		log_fatal("failed to create socket");
		return -1;
	}

	// Bind it
	if (bind_socket(sock_desc) < 0) {
		log_fatal("failed to bind socket");
		return -1;
	}

	listen(sock_desc, 1);

	// Wait for the reset
	log_debug("waiting for reset");
	if ((sock = accept(sock_desc, (struct sockaddr *) &client, (socklen_t *) sizeof(struct sockaddr_in)) < 0)) {
		log_fatal("failed to accept request");
		return -1;
	}
}
