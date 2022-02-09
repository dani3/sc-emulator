# CMake version > 3.10
cmake_minimum_required (VERSION 3.10)

project (sc-emulator LANGUAGES CXX VERSION 0.0.0)
set(CMAKE_CXX_STANDARD 17)

get_property(TEST VARIABLE PROPERTY TEST)

set(LIBS spdlog::spdlog)

if(${TEST})
  # Catch2
  list(APPEND ${LIBS} Catch2::Catch2)
  find_package(Catch2 REQUIRED)
endif()

# SPDLOG
add_subdirectory(vendor/spdlog)
include_directories(src vendor/spdlog/inlude)

add_executable(${CMAKE_PROJECT_NAME}
  src/Main.cpp
  src/Core/Log.cpp
  src/Core/Product.cpp
  src/Core/Platform.cpp
  src/Protocol/Protocol.cpp
  src/Protocol/Atr.cpp
  src/Protocol/TcpIpServer.cpp
  src/Cryptography/CRC16.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${LIBS})

if(${TEST})
  include(CTest)
  include(Catch)
  catch_discover_tests(${CMAKE_PROJECT_NAME})
endif()
