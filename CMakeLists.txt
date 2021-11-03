# CMake version > 3.10
cmake_minimum_required (VERSION 3.10)

project (sc-emulator LANGUAGES CXX VERSION 0.0.0)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/spdlog)
include_directories(src vendor/spdlog/inlude)

add_executable(${CMAKE_PROJECT_NAME} src/Main.cpp src/Core/Log.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE spdlog::spdlog)
