# SmartCard Emulator

Small SmartCard emulator written in C++17. This project was born from the fact of wanting to practice different kinds of tools and tests frameworks for C++ and Python.

## How to use

First, __install__ all the [dependencies](#dependencies) shown below. Once installed, __compile__ the emulator:

```sh
$ cmake .. -DCMAKE_BUILD_TYPE=$1 -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -G "Unix Makefiles"
$ make
```

You can now __run__ the emulator:

```sh
cd build/
./sc-emulator
```

### Dependencies

- [CMake](https://www.cmake.org)
- [Catch2](https://github.com/catchorg/Catch2)
- [Python 3.9+](https://www.python.org/)
