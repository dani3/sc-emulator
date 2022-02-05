/** \file TcpIpServer.cpp
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
 * See https://en.wikipedia.org/wiki/Nagle%27s_algorithm#Interaction_with_delayed_ACK
 */
#include "Protocol/TcpIpServer.h"

#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>

#define DEFAULT_PORT 8080

TcpIpServer *TcpIpServer::s_Server;

TcpIpServer::TcpIpServer() {
    s_ListenSocket = 0;
    s_ClientSocket = 0;
}

TcpIpServer *TcpIpServer::GetInstance() {
    if (s_Server == nullptr) {
        s_Server = new TcpIpServer();
    }

    return s_Server;
}

/**
 * \brief Initialize a TCP/IP server Upon calling a new connection can be accepted.
 */
void TcpIpServer::Init() {
    struct sockaddr_in remote;

    SC_INFO("initializing TCP/IP server at port {0}...", DEFAULT_PORT);

    // Create the socket.
    s_ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
    SC_ASSERT(s_ListenSocket >= 0, "failed to create socket...");

    usize on = 1;
    SC_ASSERT(
        setsockopt(s_ListenSocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == 0,
        "error while setting socket option...");

    // Disable Nagle's algorithm (see file header).
    SC_ASSERT(
        setsockopt(s_ListenSocket, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on)) == 0,
        "error while setting socket option...");

    remote.sin_family = AF_INET;
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(DEFAULT_PORT);

    // Set up the TCP listening socket.
    SC_ASSERT(
        bind(s_ListenSocket, (struct sockaddr *) &remote, sizeof(remote)) >= 0,
        "failed to bind socket...");

    SC_ASSERT(listen(s_ListenSocket, 1) >= 0, "unable to set socket backlog...");
}

/**
 * \brief Wait until a new connection arrives.
 *
 * \note This is a blocking method.
 */
void TcpIpServer::Accept() {
    struct sockaddr_in client;
    socklen_t client_size = sizeof(client);

    SC_INFO("listening for connections...");
    s_ClientSocket = accept(s_ListenSocket, (struct sockaddr *) &client, &client_size);
    SC_ASSERT(s_ClientSocket >= 0, "failed to accept connection...")
    SC_INFO("new connection accepted...");
}

/**
 * \brief receives `length` bytes and stores them into `buf`.
 *
 * \param buf: buffer to store the data.
 * \param length: length of the data.
 *
 * \return ReceiveResult::OK if everything went ok, ReceiveResult::FatalError if an error occured
 * and ReceiveResult::ConnectionClosed if the connection has been closed.
 */
ReceiveResult TcpIpServer::Receive(u8 *buf, usize length) {
    int result = recv(s_ClientSocket, buf, length, MSG_WAITALL);
    if (result > 0) {
        // If the reception is succesful, `recv` returns the number of bytes received.
        return ReceiveResult::Ok;

    } else if (result == 0) {
        // If `recv` returns zero it means that the connection has been closed.
        return ReceiveResult::ConnectionClosed;

    } else {
        // If it returns something else, an error occured.
        return ReceiveResult::FatalError;
    }
}

/**
 * \brief sends `length` bytes stored at `data`.
 *
 * \param data: data to be transmitted.
 * \param length: length of the data.
 */
void TcpIpServer::Send(const u8 *data, usize length) {
    SC_ASSERT(send(s_ClientSocket, data, length, 0) >= 0, "failed to transmit...");
}

/**
 * \brief Close the TCP/IP server.
 */
void TcpIpServer::Close() {
    SC_ASSERT(close(s_ClientSocket) >= 0, "failed to close server...");
}
