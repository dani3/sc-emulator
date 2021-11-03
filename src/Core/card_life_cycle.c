/**
 * \file card_life_cycle.c
 *
 * \brief
 */
#include <core/card_life_cycle.h>

static card_state_t s_state;

/**
 * \brief Get the card state.
 *
 * \return state of the card.
 */
card_state_t card_state_get(void) {
  return s_state;
}

/**
 * \brief Set a new card state.
 *
 * \param new_state new state to be set.
 *
 * \return 0 if succesful, error code otherwise.
 */
isize card_state_set(card_state_t new_state) {
  // TODO check if the transition is legal.
  s_state = new_state;
  return 0;
}
