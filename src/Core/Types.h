/**
 * \file Types.h
 *
 * \brief This file contains platform-agnostic types definitions for an X86_64 architecture.
 */
#pragma once

/// \brief 1-byte unsigned primitive type.
typedef unsigned char u8;
/// \brief 2-byte unsigned primitive type.
typedef unsigned short u16;
/// \brief 4-byte unsigned primitive type.
typedef unsigned int u32;
/// \brief 8-byte unsigned primitive type.
typedef unsigned long long u64;

/// \brief 1-byte signed primitive type.
typedef signed char i8;
/// \brief 2-byte signed primitive type.
typedef signed short i16;
/// \brief 4-byte signed primitive type.
typedef signed int i32;
/// \brief 8-byte signed primitive type.
typedef signed long long i64;

/// \brief Pointer-sized unsigned integer type.
typedef unsigned long long usize;
/// \brief Pointer-sized signed integer type.
typedef signed long long isize;
