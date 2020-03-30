#ifndef HAL_H
#define HAL_H

#include <core/types.h>

//////////////////////////////
//            IO            //
//////////////////////////////

/// \brief initializes the IO interface.
u8 io_init(void);

/// \brief receives `length` bytes and stores them into `buf`.
u8 io_receive(u8* buf, u16 length);
/// \brief sends `length` bytes stored at `buf`.
u8 io_send(u8* buf, u16 length);

#endif // HAL_H
