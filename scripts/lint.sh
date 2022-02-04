#!/bin/bash

./scripts/run-clang-tidy.py src -p build -format-style=file -header-filter=src/* -extra-arg=-std=c++17 -extra-arg=-Isrc -extra-arg=-Ivendor/spdlog/include
