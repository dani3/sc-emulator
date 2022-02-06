"""Target module that is able to communicate with the emulator."""

from __future__ import annotations

from baldwin.tcpip_client import TcpIpClient

from typing import Optional, Type
from types import TracebackType


class Target:
    """Target class."""

    COLD_RESET: int = 0x00
    TRANSMIT: int = 0x01
    EXIT: int = 0x02

    client: TcpIpClient

    def __init__(self) -> None:
        self.client = TcpIpClient()
        self.client.connect()

    def reset(self) -> bytearray:
        """Perform a cold reset and return the ATR."""

        print("[TARGET] resetting...")

        self.client.send_all((self.COLD_RESET).to_bytes(1, byteorder="little"))
        raw_length: bytearray = self.client.recv_exact(2)

        length: int = int.from_bytes(raw_length, byteorder="little", signed=False)
        atr: bytearray = self.client.recv_exact(length)

        print("[TARGET] ATR received: ", " ".join("{:02x}".format(x) for x in atr))

        return atr

    def __enter__(self) -> Target:
        return self

    def __exit__(
        self,
        exc_type: Optional[Type[BaseException]],
        exc_value: Optional[BaseException],
        traceback: Optional[TracebackType],
    ) -> None:
        self.client.send_all((self.EXIT).to_bytes(1, byteorder="little"))
        self.client.disconnect()
