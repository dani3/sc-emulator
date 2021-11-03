/**
 * \file Main.cpp
 *
 * \brief Entry point of the emulator.
 */
#include "Core/Core.h"

/**
 * \brief Main initialization.
 */
static void main_boot(void) {
  // protocol_init();
}

/**
 * \brief Entry point.
 *
 * \return Unused.
 */
int main() {
  Log::Init();
  SC_INFO(
      "starting sc-emulator (v{0}.{1}.{2})...", SC_VERSION_MAJOR, SC_VERSION_MINOR,
      SC_VERSION_PATCH);
  //
  //  // Initialize the TCP/IP server.
  //  server_init();
  //
  //  // `set_jmp` needs to be called from the main function as it doesn't get out of scope ever
  //  and,
  //  // hence, deallocated. This prevents the possibility of creating some kind of abstraction
  //  layer. reset_action_t reason = setjmp(g_reset_checkpoint); if (reason == EXIT) {
  //    log_info("shutting down sc-emulator...");
  //
  //    // Free resources.
  //    platform_destroy();
  //    // Shutdown the server.
  //    server_close();
  //
  //    return 0;
  //  }
  //
  //  // Initialize the device to emulate the real target as close as possible.
  //  platform_create();
  //  // Wait for a connection.
  //  server_accept();
  //
  //  // Initialize the OS.
  //  main_boot();
  //
  //  process_commands();
  //
  return 0;
}
