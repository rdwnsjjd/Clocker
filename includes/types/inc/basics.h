// Copyright (C) 2021 rdwn
// 
// This file is part of Clocker.
// 
// Clocker is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Clocker is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Clocker.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __TYPES_INC_BASICS_H
#define __TYPES_INC_BASICS_H

typedef char         Int8;
typedef short int    Int16;
typedef       int    Int32;
typedef long  int    Int64;
typedef long  double Int128;

typedef unsigned char         UInt8;
typedef unsigned short int    UInt16;
typedef unsigned       int    UInt32;
typedef unsigned long  int    UInt64;

typedef char         Char;
typedef char         Byte;
typedef char*        Str;
typedef char*        Bytes;

typedef float               Float;
typedef double              Double;
typedef void                Void;
typedef void*               Hndl;
typedef void*               Ptr;
typedef enum {False, True}  Bool;

typedef          long  int    SSize;
typedef unsigned long  int    Size;
typedef unsigned long  int    Id;
typedef unsigned long  int    Idx;

#define INVALID_ID    (Id)0
#define INVALID_HNDL  (Hndl)0

#define INF_UINT8  (UInt8)-1
#define INF_UINT16 (UInt16)-1
#define INF_UINT32 (UInt32)-1
#define INF_UINT64 (UInt64)-1

#endif // __TYPES_INC_BASICS_H