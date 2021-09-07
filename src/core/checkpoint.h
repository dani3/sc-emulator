/**
 * \file checkpoint.c
 *
 * \brief Set of 'checkpoints' that can be left in the code.
 */
#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <setjmp.h>

/**
 * \brief Action to be performed when a reset has been received.
 */
typedef enum {
  COLD_RESET = 1,            ///< Perform a cold reset.
  ACCEPT_NEW_CONNECTION = 2, ///< Accept a new connection.
  EXIT = 3,                  ///< Exit the process.
} reset_action_t;

/// \brief When a reset is received, this is the `jmp_buf` to be used.
extern jmp_buf g_reset_checkpoint;

#endif
