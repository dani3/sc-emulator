#!/bin/bash

mkdir -p build/
cd build/
cmake .. -DCMAKE_BUILD_TYPE=$1 -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -G "Unix Makefiles"
