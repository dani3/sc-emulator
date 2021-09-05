/**
 * \file main.c
 *
 * \brief Entry point of the emulator.
 */
#include <core/core.h>

#include <protocol/tcpip_server.h>

/**
 * \brief Entry point.
 *
 * \return Unused.
 */
int main() {
  log_info("starting sc-emulator");

  // Initialize the device to emulate the real target as close as possible.
  platform_create();
  server_init();
  server_accept();

  // Send/receive loop
  while (true) {
  }

  return 0;
}
