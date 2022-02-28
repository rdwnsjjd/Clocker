#ifndef _INC_DEFS_GEN_H_
#define _INC_DEFS_GEN_H_

#include "type_defs.h"
#include "framework/prims/debug.h"

typedef union {
    char_t             i8;
    u8_t               u8;
    i16_t              i16;
    u16_t              u16;
    i32_t              i32;
    u32_t              u32;
    i64_t              i64;
    u64_t              u64;
    f32_t              f32;
    f64_t              d64;
    i128_t             d128;
    size_t             size;
    ssize_t            ssize;
    handle_t           ptr;
    str_t              str;
    bytes_t            pi8;
    i32_t*             pi32;
    f32_t*             pf32;
    f64_t*             pd64;
}
gen_t;

#define G_NONE       (gen_t) 0
#define _(data_)     (gen_t) data_

#endif // _INC_DEFS_GEN_H_
