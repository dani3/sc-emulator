/**
 * \file types.h
 *
 * \brief Header file that contains the types of the platform.
 */
#ifndef TYPES_H
#define TYPES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef unsigned long long usize;
typedef signed long long isize;

#ifndef NULL
#  define NULL 0
#endif

#ifndef nullptr
#  define nullptr 0
#endif

#ifndef true
#  define true 1
#endif

#ifndef false
#  define false 1
#endif

#endif // #ifndef TYPES_H
