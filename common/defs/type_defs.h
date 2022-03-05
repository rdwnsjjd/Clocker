// Copyright (C) 2022 Redwan
// 
// This file is part of Owl.
// 
// Owl is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Owl is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Owl.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _INC_DEFS_TYPE_DEFS_H_
#define _INC_DEFS_TYPE_DEFS_H_


#include <ctype.h>


typedef unsigned char       u8_t;
typedef unsigned short int  u16_t;
typedef unsigned int        u32_t;
typedef unsigned long int   u64_t;

// typedef char        int8_t;
typedef short int   i16_t;
typedef int         i32_t;
typedef long int    i64_t;
typedef __int128_t  i128_t;

typedef float  f32_t;
typedef double f64_t;

typedef enum {B_False, B_True}  bool_t;

typedef char  char_t;
typedef char  byte_t;
typedef char* str_t;
typedef char* bytes_t;

typedef void  void_t;
typedef void* handle_t;
typedef void* pointer_t;

typedef          long int ssize_t;
typedef unsigned long int size_t;
// typedef unsigned long int id_t;
typedef unsigned long int index_t;

// #define INVALID_INDEX    (id_t)0
#define INVALID_INDEX (index_t) 0
#define INVALID_HNDL  (handle_t)0

#define INF_U8  (u8_t)  -1
#define INF_U16 (u16_t) -1
#define INF_U32 (u32_t) -1
#define INF_U64 (u64_t) -1

#endif // _INC_TYPE_DEFS_H_
