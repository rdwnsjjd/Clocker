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

#ifndef __TYPES_INC_OPTION_H
#define __TYPES_INC_OPTION_H

#include "./basics.h"
#include "./gen_type.h"
#include "./result.h"

typedef struct {
    GenType     some;
    Bool        is_none;
}
Opt;

#define opt_is_some(opt_)             (!(opt_.is_none))
#define opt_is_none(opt_)             (opt_.is_none)
#define some(data_)                   (Opt) {.some = (GenType) data_, .is_none = False}
#define None                          (Opt) {.some = (GenType) 0,     .is_none = True}


#define soft_assert_opt(opt_, msg_, ...)           do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return False; } }                      while(0)
#define soft_assert_opt_ret_int(opt_, msg_, ...)   do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return -1; } }                         while(0)
#define soft_assert_opt_ret_ptr(opt_, msg_, ...)   do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return INVALID_HNDL; } }               while(0)
#define soft_assert_opt_ret_id(opt_, msg_, ...)    do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return INVALID_ID; } }                 while(0)
#define soft_assert_opt_ret_float(opt_, msg_, ...) do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return (Float)-1; } }                  while(0)
#define soft_assert_opt_ret_void(opt_, msg_, ...)  do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return ; } }                           while(0)
#define soft_assert_opt_ret_err(opt_, msg_, ...)   do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return (Result)err(EK_Gen, GEN_ERR_CODE); } } while(0)
#define soft_assert_ret_opt(exp_, msg_, ...)       do { if (!(exp_))           { debug_err(msg_, ## __VA_ARGS__); return None; } } while(0)

#define soft_assert_opt_wrn(exp_, msg_, ...)    do { if (opt_is_none(opt_)) { debug_wrn(msg_, ## __VA_ARGS__); } } while(0)
#define soft_assert_opt_inf(exp_, msg_, ...)    do { if (opt_is_none(opt_)) { debug_inf(msg_, ## __VA_ARGS__); } } while(0)
#define soft_assert_opt_log(exp_, msg_, ...)    do { if (opt_is_none(opt_)) { debug_log(msg_, ## __VA_ARGS__); } } while(0)

#define soft_assert_opt_break(exp_, msg_, ...)        do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_opt_continue(exp_, msg_, ...)     do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_opt_break_wrn(exp_, msg_, ...)    do { if (opt_is_none(opt_)) { debug_wrn(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_opt_continue_wrn(exp_, msg_, ...) do { if (opt_is_none(opt_)) { debug_wrn(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_opt_break_inf(exp_, msg_, ...)    do { if (opt_is_none(opt_)) { debug_inf(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_opt_continue_inf(exp_, msg_, ...) do { if (opt_is_none(opt_)) { debug_inf(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_opt_break_log(exp_, msg_, ...)    do { if (opt_is_none(opt_)) { debug_log(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_opt_continue_log(exp_, msg_, ...) do { if (opt_is_none(opt_)) { debug_log(msg_, ## __VA_ARGS__); continue;} } while(0)

#define match_opt(opt_, if_matches_, else_)     if (opt_is_some(opt_)) {GenType data = opt_.some; if_matches_} else {else_}



#endif // __TYPES_INC_OPTION_H