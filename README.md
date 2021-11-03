# SmartCard Emulator

[![build](https://github.com/dani3/sc-emulator/actions/workflows/build.yml/badge.svg)](https://github.com/dani3/sc-emulator/actions/workflows/build.yml)
[![test](https://github.com/dani3/sc-emulator/actions/workflows/unit-test.yml/badge.svg)](https://github.com/dani3/sc-emulator/actions/workflows/unit-test.yml)

Small SmartCard emulator written in C++. This project stemmed from the fact of wanting to practice different kinds of technologies, such as Ceedling, Python and minor C related things.

## How to use

First, install all the dependencies shown below. Once installed, compile the emulator:

```sh
$ ceedling clobber release
```

You can now run the emulator:

```sh
$ ./build/release/sc-emulator
```

### Dependencies

- [Ceedling](https://www.throwtheswitch.org/ceedling)
- [Python 3.9](https://www.python.org/)
