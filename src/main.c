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
  log_info(
      "starting sc-emulator (v%i.%i.%i)...", SC_VERSION_MAJOR, SC_VERSION_MINOR, SC_VERSION_PATCH);

  // Initialize the device to emulate the real target as close as possible.
  platform_create();
  // Initialize the TCP/IP server.
  server_init();
  // Wait for a connection.
  server_accept();

  return 0;
}
