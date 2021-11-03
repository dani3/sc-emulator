/**
 * \file command_processor.c
 *
 * \brief
 */
#include <core/core.h>

#include <core/card_life_cycle.h>
#include <core/command_processor.h>
#include <mmu/mmu.h>
#include <protocol/protocol.h>
#include <protocol/status_word.h>

// Class bytes of the commands supported
#define CLA_PERSONALIZATION_CMD 0x10

// Instruction bytes of the commands supported

// Personalization commands
#define INS_INIT_COMMAND   0x10
#define INS_FINISH_COMMAND 0xF0

/**
 * \brief Init command used to initialize the card. After this command is issued the personalization
 * commands become available.
 *
 * \return Status word to be returned.
 */
static u16 process_init_command(void) {
  mmu_fill(get_nvm_start_as_mut(), 0, NVM_SIZE);

  card_state_set(INITIALIZED);
}

/**
 * \brief Main command processor.
 *
 * It essentially acts as a dispatcher.
 */
void process_commands(void) {
  apdu_t* apdu;

  while (true) {
    apdu = protocol_receive();

    // TODO secure this block.
    if (card_state_get() == BLOCKED) {
      protocol_set_sw(STATUS_WORD_WRONG_STATE, apdu);

    } else {
      switch (apdu->cla) {
        case CLA_PERSONALIZATION_CMD:
          switch (apdu->ins) {
            case INS_INIT_COMMAND:
              break;

            default:
              protocol_set_sw(STATUS_WORD_UNKNOWN_INS, apdu);
              break;
          }
          break;

        default:
          protocol_set_sw(STATUS_WORD_UNKNOWN_CLASS, apdu);
          break;
      }
    }

    protocol_send(apdu);
  }
}
