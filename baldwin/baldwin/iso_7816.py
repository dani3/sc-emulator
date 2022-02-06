"""Module that contains the implementation of a Command and Response APDU as specified in the ISO7816."""

from typing import Optional, List


class Command:
    """C-Apdu class as defined in the ISO-7816."""

    cla: int
    ins: int
    p1: int
    p2: int
    p3: int
    data: Optional[List[int]]

    def __init__(
        self,
        cla: int,
        ins: int,
        p1: int,
        p2: int,
        p3: Optional[int],
        data: Optional[List[int]],
    ) -> None:

        self.cla = cla
        """Class byte."""

        self.ins = ins
        """Instruction byte."""

        self.p1 = p1
        """P1 byte."""

        self.p2 = p2
        """P2 byte."""

        self.p3 = 0 if p3 is None else p3
        """P3 byte."""

        self.data = data
        """Data field."""


class Response:
    """R-Apdu class as defined in the ISO-7816."""

    sw1: int
    sw2: int
    data: Optional[List[int]]

    def __init__(self, sw1: int, sw2: int, data: Optional[List[int]]) -> None:

        self.sw1 = sw1
        """First byte of the Status Word."""

        self.sw2 = sw2
        """Second byte of the Status Word."""

        self.data = data
        """Data field."""

    def is_sw_9000(self) -> bool:
        """Return true if the status word is 0x9000."""
        return self.sw1 == 0x90 and self.sw2 == 0x00
