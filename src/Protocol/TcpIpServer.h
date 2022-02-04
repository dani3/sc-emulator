#pragma once

#include "Core/Core.h"

/**
 * \brief \todo
 */
enum class ReceiveResult {
    Ok,               ///< \todo
    FatalError,       ///< \todo
    ConnectionClosed, ///< \todo
};

/**
 * \brief Tcp/Ip server class.
 *
 * This class is implemented as a singleton as only one server should be running.
 */
class TcpIpServer {
public:
    // It cannot be cloneable.
    TcpIpServer(TcpIpServer &other) = delete;
    // It cannot be assignable.
    void operator=(const TcpIpServer &other) = delete;

    static TcpIpServer *GetInstance();

    // Initialize the TCP/IP server.
    void Init();
    // Wait until a new connection arrives.
    void Accept();
    // Send a stream of bytes.
    void Send(const u8 *data, usize length);
    // Receive a stream of bytes.
    ReceiveResult Receive(u8 *data, usize length);
    // Close the TCP/IP server.
    void Close();

private:
    TcpIpServer();

    static TcpIpServer *s_server;

    // Socket used ot listen for new connections.
    int s_listen_socket;
    // Client socket used for communicating with an accepted connection.
    int s_client_socket;
};
