#ifndef _INC_DEFS_OPT_H_
#define _INC_DEFS_OPT_H_

#include "type_defs.h"
#include "gen.h"
// #include "res.h"

typedef struct {
    gen_t     some;
    bool_t    is_none;
}
opt_t;

#define opt_is_some(opt_)             (!(opt_.is_none))
#define opt_is_none(opt_)             (opt_.is_none)
#define some(data_)                   (opt_t) {.some = (gen_t) data_, .is_none = B_False}
#define None                          (opt_t) {.some = (gen_t) 0,     .is_none = B_True}
#define get_some(opt_)                (opt_).some

// #define match_opt(opt_, if_matches_, else_)     if (opt_is_some(opt_)) {gen_t data = opt_.some; if_matches_} else {else_}

#endif // _INC_DEFS_OPT_H_