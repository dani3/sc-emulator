/** \file x86_io.c
 * \brief
 *
 */
#include <core/core.h>
#include <core/logger.h>

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT    8080


/** \fn short create_socket(void)
 * \brief creates a socket for the server and makes it passive such that
 * we can wait for connections on it later.
 *
 * \param
 *
 * \return
 */
static short create_socket(void) {
	log_debug("create socket...");
	return socket(AF_INET, SOCK_STREAM, 0);
}

/** \fn int bind_socket(short socket)
 * \brief binds the created socket to a specific port.
 *
 * \param
 *
 * \return
 */
static int bind_socket(short socket) {
	struct sockaddr_in remote = { 0 };

	remote.sin_family = AF_INET;
	remote.sin_addr.s_addr = htonl(INADDR_ANY);
	remote.sin_port = htons(PORT);

	log_debug("bind socket...");
	return bind(socket, (struct sockaddr *) &remote, sizeof(remote));
}

/** \fn
 * \brief
 *
 * \return
 */
int io_init(void) {
	int sock_desc;

	if ((sock_desc = create_socket()) < 0) {
		log_fatal("failed to create socket");
		return -1;
	}

	if (bind_socket(sock_desc) < 0) {
		log_fatal("failed to bind socket");
		return -1;
	}
}
