/**
 * \file card_life_cycle.h
 *
 * \brief
 */
#ifndef CARD_LIFE_CYCLE_H
#define CARD_LIFE_CYCLE_H

#include <core/core.h>

/// \brief
typedef enum { UNINITIALIZED = 0, INITIALIZED, READY, BLOCKED } card_state_t;

// Get the card state.
card_state_t card_state_get(void);
// Set a new card state.
isize card_state_set(card_state_t new_state);

#endif
