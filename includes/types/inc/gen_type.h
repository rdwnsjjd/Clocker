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