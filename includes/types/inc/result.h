#ifndef __TYPES_INC_RESULT_H
#define __TYPES_INC_RESULT_H

#include <errno.h>

#include "./basics.h"
#include "./gen_type.h"

typedef enum {
    EK_Gen = 0,
    EK_Perm,
    EK_Not_Found,
    EK_Access,
    EK_Busy,
    EK_Exist,
    EK_Notdir,
    EK_Inval,
    EK_Openf,
    EK_Closef,
    EK_Createf,
    EK_Connectf,
    EK_Bindf,
    EK_Insrtf,
    EK_Appndf,
    EK_Pushf,
    EK_Popf,
    EK_Stckf,
    EK_Allcf,
    EK_Notimpl,
}
ErrKind;

typedef Id ErrNum;

typedef struct {
    ErrKind         e_kind;
    ErrNum          e_num;
}
Err;

typedef struct {
    GenType     ok;
    Err         err;
    Bool        is_ok;
}
Result;

#define GEN_ERR_CODE                0
#define is_ok(res_)                 (res_.is_ok) ? (res_.ok) : (G_NONE)
#define res_is_ok(res_)             (res_.is_ok)
#define ok(data_)                   (Result) {.ok = (GenType)data_, .err = {0}, .is_ok = True}
#define err(err_kind_, err_num_)    (Result) {.ok = (GenType)0    , .err = {.e_kind = err_kind_, .e_num = err_num_}, .is_ok = False}

#define res_get_data(res_)          res_.ok
#define res_get_err(res_)           res_.err

#define soft_assert_res(res_, msg_, ...)           do { if (!res_is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return False; } }                              while(0)
#define soft_assert_res_ret_int(res_, msg_, ...)   do { if (!res_is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return -1; } }                                 while(0)
#define soft_assert_res_ret_ptr(res_, msg_, ...)   do { if (!res_is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return INVALID_HNDL; } }                       while(0)
#define soft_assert_res_ret_id(res_, msg_, ...)    do { if (!res_is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return INVALID_ID; } }                         while(0)
#define soft_assert_res_ret_float(res_, msg_, ...) do { if (!res_is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return (Float)-1; } }                          while(0)
#define soft_assert_res_ret_void(res_, msg_, ...)  do { if (!res_is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return ; } }                                   while(0)
#define soft_assert_res_ret_err(res_, msg_, ...)   do { if (!res_is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return (Result)err(EK_Gen, GEN_ERR_CODE); } }  while(0)
#define soft_assert_res_ret_gen(res_, msg_, ...)   do { if (!res_is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return G_NONE;} }                               while(0)

#define soft_assert_res_wrn(exp_, msg_, ...)    do { if (!res_is_ok(res_)) { debug_wrn(msg_, ## __VA_ARGS__); } } while(0)
#define soft_assert_res_inf(exp_, msg_, ...)    do { if (!res_is_ok(res_)) { debug_inf(msg_, ## __VA_ARGS__); } } while(0)
#define soft_assert_res_log(exp_, msg_, ...)    do { if (!res_is_ok(res_)) { debug_log(msg_, ## __VA_ARGS__); } } while(0)

#define soft_assert_res_break(exp_, msg_, ...)        do { if (!res_is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_res_continue(exp_, msg_, ...)     do { if (!res_is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_res_break_wrn(exp_, msg_, ...)    do { if (!res_is_ok(res_)) { debug_wrn(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_res_continue_wrn(exp_, msg_, ...) do { if (!res_is_ok(res_)) { debug_wrn(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_res_break_inf(exp_, msg_, ...)    do { if (!res_is_ok(res_)) { debug_inf(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_res_continue_inf(exp_, msg_, ...) do { if (!res_is_ok(res_)) { debug_inf(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_res_break_log(exp_, msg_, ...)    do { if (!res_is_ok(res_)) { debug_log(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_res_continue_log(exp_, msg_, ...) do { if (!res_is_ok(res_)) { debug_log(msg_, ## __VA_ARGS__); continue;} } while(0)


// #define soft_assert_ret_res(expr_, msg_, ...)    do { if (!(expr_)) { debug_err(msg_, ## __VA_ARGS__); return (Result)ok(0); } } while(0)
#define soft_assert_ret_err(expr_, msg_, ...)    do { if (!(expr_)) { debug_err(msg_, ## __VA_ARGS__); return err(EK_Gen, GEN_ERR_CODE); } } while(0)


#define match_res(res_, if_matches_, else_)     (res_is_ok(res_)) ? {GenType data = res_.ok; if_matches_} : {else_}


static inline Str error_print(Err err) {
    debug_err("Not implemented yet!");
}


#endif // __TYPES_INC_RESULT_H