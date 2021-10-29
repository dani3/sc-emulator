/**
 * \file status_word.h
 *
 * \brief Collection of all the status words the system can reply.
 */
#ifndef STATUS_WORD_H
#define STATUS_WORD_H

#define STATUS_WORD_OK 0x9000

#define STATUS_WORD_UNKNOWN_INS   0x7D00 ///< Unknown class.
#define STATUS_WORD_UNKNOWN_CLASS 0x7E00 ///< Unknown class.
#define STATUS_WORD_WRONG_STATE   0x7FFF ///< Card in wrong state.

#endif
