#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "tcp_client.h"

#define PORT    8080

static short create_socket(void) {
    return socket(AF_INET, SOCK_STREAM, 0);
}

static int connect_to_socket(short socket) {
    struct sockaddr_in remote = { 0 };

    remote.sin_addr.s_addr = inet_addr("127.0.0.1");
    remote.sin_family = AF_INET;
    remote.sin_port = htons(PORT);

    return connect(socket, (struct sockaddr *) &remote, sizeof(struct sockaddr_in));
}

int start_client(void) {
    short socket = create_socket();
    if (socket < 0) {
        printf("could not create socket");
        return -1;
    }

    if (connect_to_socket(socket) < 0) {
        printf("could not connect to socket");
        return -1;
    }

    return socket;
}

int transmit(int socket, char* data, short length) {
    struct timeval tv;

    tv.tv_sec = 20;
    tv.tv_usec = 0;

    if (setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, (char *) &tv, sizeof(tv)) < 0) {
        printf("error transmitting data");
        return -1;
    }

    return send(socket, data, length, 0);
}

int receive(int socket, char* output, short length) {
    struct timeval tv;

    tv.tv_sec = 20;
    tv.tv_usec = 0;

    if (setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv, sizeof(tv)) < 0) {
        printf("error receiving");
        return -1;
    }

    return recv(socket, output, length, 0);
}

void disconnect(int socket) {
    close(socket);
}
