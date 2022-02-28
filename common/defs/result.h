#ifndef __TYPES_INC_RESULT_H
#define __TYPES_INC_RESULT_H

#include <errno.h>
// #include <stdlib.h>

#include "type_defs.h"
#include "gen.h"


typedef size_t err_num_t;

typedef enum {
    ek_gen = 0,
    ek_unexpected_eof,
    ek_unexpected_error,
    ek_perm,
    ek_not_found,
    ek_access,
    ek_busy,
    ek_exist,
    ek_notdir,
    ek_inval,
    ek_stck,
    ek_openf,
    ek_closef,
    ek_createf,
    ek_connectf,
    ek_bindf,
    ek_insrtf,
    ek_appndf,
    ek_pushf,
    ek_popf,
    ek_allcf,
    ek_not_impl,
}
err_kind_t;


typedef struct {
    err_kind_t         e_kind;
    err_num_t          e_num;
}
err_t;


typedef struct {
    gen_t       ok;
    err_t       err;
    bool_t      is_ok;
}
result_t;


#define GEN_ERR_CODE                0
#define is_ok(res_)                 (res_.is_ok)
#define res_get_data(res_)          ((res_.is_ok) ? (res_.ok) : (G_NONE))
#define res_get_error(res_)         (res_.err)
#define ok(data_)                   (result_t) {.ok = (gen_t)data_, .err = {0}, .is_ok = B_True}
#define err(err_kind_)              (result_t) {.ok = (gen_t)0    , .err = {.e_kind = err_kind_, .e_num = GEN_ERR_CODE}, .is_ok = B_False}

#define unwrap(data_, res_)         if(is_ok(res_)) data_ = res_.ok; else {debug_err("The program paniced because of (%s)!", e_print(res_.err)); exit(-1);}

#define match_res(res_, if_matches_, else_)     (res_is_ok(res_)) ? {gen_t data = res_.ok; if_matches_} : {else_}


static inline str_t e_print(err_t err) {
    switch (err.e_kind) {
        case ek_gen:
            return "General Error";
            break;
        case ek_unexpected_eof:
            return "Unexpected End Of File Error";
            break;
        case ek_perm:
            return "Permision Error";
            break;
        case ek_unexpected_error:
            return "Unexpected Error";
            break;
        case ek_access:
            return "Access Error";
            break;
        case ek_busy:
            return "Resource Is Busy Error";
            break;
        case ek_exist:
            return "Already Exists Error";
            break;
        case ek_notdir:
            return "Not A Directory Error";
            break;
        case ek_inval:
            return "Invalid Data Error";
            break;
        case ek_openf:
            return "Opening Failure";
            break;
        case ek_closef:
            return "Closing Failure";
            break;
        case ek_createf:
            return "Creation Failure";
            break;
        case ek_connectf:
            return "Connection Failure";
            break;
        case ek_bindf:
            return "Binding Failure";
            break;
        case ek_insrtf:
            return "Insertion Failure";
            break;
        case ek_appndf:
            return "Appending Failure";
            break;
        case ek_pushf:
            return "Pushing Failure";
            break;
        case ek_popf:
            return "Poping Failure";
            break;
        case ek_stck:
            return "Stack Error";
            break;
        case ek_allcf:
            return "Allocation Failure";
            break;
        case ek_not_impl:
            return "Not Implemented";
            break;
    
        default:
            return "Unknown Error";
            break;
    }
}


#endif // __TYPES_INC_RESULT_H