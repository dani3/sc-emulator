#pragma once

#include "Core/Core.h"

/**
 * \brief Enum that represents the types of errors that can happen upon reception.
 */
enum class ReceiveResult {
    Ok,               ///< Some data has been received.
    FatalError,       ///< Unrecoverable error.
    ConnectionClosed, ///< The connection has been closed.
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

    static TcpIpServer *s_Server;

    // Socket used ot listen for new connections.
    int m_ListenSocket;
    // Client socket used for communicating with an accepted connection.
    int m_ClientSocket;
};
