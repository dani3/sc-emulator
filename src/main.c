/**
 * \file main.c
 *
 * \brief Entry point of the emulator.
 */
#include <core/core.h>

#include <core/checkpoint.h>
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

  // `set_jmp` needs to be called from the main function as it doesn't get out of scope ever and,
  // hence, deallocated. This prevents the possibility of creating some kind of abstraction layer.
  reset_action_t reason = setjmp(g_reset_checkpoint);
  if (reason == EXIT) {
    log_info("shutting down sc-emulator...");

    // Free resources.
    platform_destroy();
    // Shutdown the server.
    server_close();
  }

  return 0;
}
