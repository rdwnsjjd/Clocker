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

#ifndef __TYPES_INC_GEN_TYPE_H
#define __TYPES_INC_GEN_TYPE_H

#include "./basics.h"
#include "../../prims/inc/debug.h"
#include "./option.h"


typedef union {
    Int8                i8;
    UInt8               u8;
    Int16               i16;
    UInt16              u16;
    Int32               i32;
    UInt32              u32;
    Int64               i64;
    UInt64              u64;
    Float               f32;
    Double              d64;
    Int128              d128;
    Hndl                ptr;
    Str                 str;
    Bytes               pi8;
    Int32*              pi32;
    Float*              pf32;
    Double*             pd64;
}
GenType;

#define G_NONE          (GenType)0
#define gen_type(data_) (GenType)data_

#define soft_assert_ret_gen(exp_, msg_, ...)      do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return G_NONE; } } while(0)

#endif // __TYPES_INC_GEN_TYPE_H