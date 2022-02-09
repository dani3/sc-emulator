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
    m_ListenSocket = -1;
    m_ClientSocket = -1;
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

    SC_TRACE("initializing TCP/IP server at port {0}...", DEFAULT_PORT);

    // Create the socket.
    m_ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
    SC_ASSERT(m_ListenSocket >= 0, "failed to create socket...");

    usize on = 1;
    int result = setsockopt(m_ListenSocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    SC_ASSERT(result == 0, "error while setting socket option...");

    // Disable Nagle's algorithm (see file header).
    result = setsockopt(m_ListenSocket, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on));
    SC_ASSERT(result == 0, "error while setting socket option...");

    remote.sin_family = AF_INET;
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(DEFAULT_PORT);

    // Set up the TCP listening socket.
    result = bind(m_ListenSocket, (struct sockaddr *) &remote, sizeof(remote));
    SC_ASSERT(result >= 0, "failed to bind socket...");

    result = listen(m_ListenSocket, 1);
    SC_ASSERT(result >= 0, "unable to set socket backlog...");
}

/**
 * \brief Wait until a new connection arrives.
 *
 * \note This is a blocking method.
 */
void TcpIpServer::Accept() {
    struct sockaddr_in client;
    socklen_t client_size = sizeof(client);

    SC_TRACE("listening for connections...");
    m_ClientSocket = accept(m_ListenSocket, (struct sockaddr *) &client, &client_size);
    SC_ASSERT(m_ClientSocket >= 0, "failed to accept connection...")
    SC_TRACE("new connection accepted...");
}

/**
 * \brief Receive `length` bytes and stores them into `buf`.
 *
 * \param buf: buffer to store the data.
 * \param length: length of the data.
 *
 * \return ReceiveResult::OK if everything went ok, ReceiveResult::FatalError if an error occured
 * and ReceiveResult::ConnectionClosed if the connection has been closed.
 */
ReceiveResult TcpIpServer::Receive(u8 *buf, usize length) {
    auto result = recv(m_ClientSocket, buf, length, MSG_WAITALL);
    if (result > 0) {
        // If the reception is succesful, `recv` returns the number of bytes received.
        return ReceiveResult::Ok;

    } else if (result == 0) {
        // If `recv` returns zero it means that the connection has been closed.
        return ReceiveResult::ConnectionClosed;

    } else {
        SC_ERROR("error receiving packet, perror = {0}", errno);
        // If it returns something else, an error occured.
        return ReceiveResult::FatalError;
    }
}

/**
 * \brief Send `length` bytes stored at `data`.
 *
 * \param data: data to be transmitted.
 * \param length: length of the data.
 */
void TcpIpServer::Send(const u8 *data, usize length) {
    auto result = send(m_ClientSocket, data, length, 0);
    SC_ASSERT(result >= 0, "failed to transmit...");
}

/**
 * \brief Close the TCP/IP server.
 */
void TcpIpServer::Close() {
    SC_ASSERT(close(m_ClientSocket) >= 0, "failed to close server...");
}
