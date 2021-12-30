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

#ifndef __PRIMS_INC_ASSERT_H
#define __PRIMS_INC_ASSERT_H

#include "./debug.h"
#include "../../types/inc/basics.h"

#define assert_eq(exp1_, exp2_)     (exp1_ == exp2_) ? True : False
#define assert_ne(exp1_, exp2_)     (exp1_ == exp2_) ? False; : True
#define assert_be(exp1_, exp2_)     (exp1_ >= exp2_) ? True; : False
#define assert_le(exp1_, exp2_)     (exp1_ <= exp2_) ? True; : False
#define assert_ez(exp1_)            assert_eq(exp1_, 0)
#define assert_nez(exp1_)           assert_ne(exp1_, 0)
#define assert_bez(exp1_)           assert_be(exp1_, 0)
#define assert_lez(exp1_)           assert_le(exp1_, 0)

#define soft_assert(exp_, msg_, ...)              do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return False; } }        while(0)
#define soft_assert_ret(exp_, ret_, msg_, ...)    do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return ret_; } }         while(0)
#define soft_assert_ret_int(exp_, msg_, ...)      do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return -1; } }           while(0)
#define soft_assert_ret_ptr(exp_, msg_, ...)      do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return INVALID_HNDL; } } while(0)
#define soft_assert_ret_id(exp_, msg_, ...)       do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return INVALID_ID; } }   while(0)
#define soft_assert_ret_float(exp_, msg_, ...)    do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return (Float)-1; } }    while(0)
#define soft_assert_ret_void(exp_, msg_, ...)     do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return ; } }             while(0)

#define soft_assert_wrn(exp_, msg_, ...)              do { if (!(exp_)) { debug_wrn(msg_, ## __VA_ARGS__); } } while(0)
#define soft_assert_inf(exp_, msg_, ...)              do { if (!(exp_)) { debug_inf(msg_, ## __VA_ARGS__); } } while(0)
#define soft_assert_log(exp_, msg_, ...)              do { if (!(exp_)) { debug_log(msg_, ## __VA_ARGS__); } } while(0)

#define soft_assert_break(exp_, msg_, ...)         do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_continue(exp_, msg_, ...)      do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_break_wrn(exp_, msg_, ...)     do { if (!(exp_)) { debug_wrn(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_continue_wrn(exp_, msg_, ...)  do { if (!(exp_)) { debug_wrn(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_break_inf(exp_, msg_, ...)     do { if (!(exp_)) { debug_inf(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_continue_inf(exp_, msg_, ...)  do { if (!(exp_)) { debug_inf(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_break_log(exp_, msg_, ...)     do { if (!(exp_)) { debug_log(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_continue_log(exp_, msg_, ...)  do { if (!(exp_)) { debug_log(msg_, ## __VA_ARGS__); continue;} } while(0)

#endif // __PRIMS_INC_ASSERT_H