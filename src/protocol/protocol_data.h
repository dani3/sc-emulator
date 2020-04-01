/** \file protocol_data.h
 *\brief module that declares protocol data to be shared across modules.
 */
#ifndef PROTOCOL_DATA_H
#define PROTOCOL_DATA_H

#include <core/types.h>

#define IO_BUFFER_SIZE            260

#define IO_BUFFER_APDU_OFFSET       0
#define IO_BUFFER_DATA_OFFSET       5

extern u8 io_buffer[IO_BUFFER_SIZE];
extern u16 sw;

#endif // #ifndef PROTOCOL_DATA_H