"""TCP/IP client implementation for testing the sc-emulator."""

from __future__ import annotations

from typing import Optional, Type
from types import TracebackType

import socket


class TcpIpClientException(Exception):
    """Custom exception."""

    message: str

    def __init__(self, message: str) -> None:
        super().__init__()

        self.message = message
        """Exception message."""

    def __str__(self) -> str:
        return self.message


class TcpIpClient:
    """TCP/IP client implementation."""

    host: str
    port: int
    connection: Optional[socket.socket]

    def __init__(self, host: str = "localhost", port: int = 8080) -> None:
        self.host = host
        """Host to bind the socket to."""

        self.port = port
        """Port number to bind the socket to."""

        self.connection = None

    def connect(self) -> None:
        """Establish a connection to server."""

        print("connecting...")

        if self.connection is not None:
            raise TcpIpClientException("Connection already established.")

        s: socket.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        s.connect((self.host, self.port))

        self.connection = s
        print("connected.")

    def disconnect(self) -> None:
        """Disconnect."""

        print("disconnecting...")

        if self.connection is None:
            return

        self.connection.shutdown(socket.SHUT_RDWR)
        self.connection.close()
        print("disconnected.")

    def send_all(self, msg: bytes) -> None:
        """Send given bytes on the socket."""

        if self.connection is None:
            raise TcpIpClientException("Connection not established.")

        self.connection.sendall(msg)

    def recv_exact(self, remaining: int) -> bytearray:
        """Read an exact number of bytes from the socket."""

        if self.connection is None:
            raise TcpIpClientException("Connection not established.")

        received: bytearray = bytearray()

        while remaining > 0:
            buf = self.connection.recv(remaining)
            if not buf:
                raise TcpIpClientException("Remote hangup")

            received += buf
            remaining -= len(buf)

        return received

    def __enter__(self) -> TcpIpClient:
        return self

    def __exit__(
        self,
        exc_type: Optional[Type[BaseException]],
        exc_value: Optional[BaseException],
        traceback: Optional[TracebackType],
    ) -> None:
        self.disconnect()


COLD_RESET: int = 0x00
TRANSMIT: int = 0x01
EXIT: int = 0x02


def main() -> None:
    """Entry point."""
    with TcpIpClient() as client:
        client.connect()
        client.send_all((TRANSMIT).to_bytes(1, byteorder="big"))
        client.send_all((5).to_bytes(2, byteorder="big"))
        client.send_all(bytes([0x01, 0x02, 0x03, 0x04, 0x05]))


if __name__ == "__main__":
    main()
