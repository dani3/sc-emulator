"""Test script."""

from target import Target


def main() -> None:
    """Entry point."""
    with Target() as target:
        target.reset()


if __name__ == "__main__":
    main()
