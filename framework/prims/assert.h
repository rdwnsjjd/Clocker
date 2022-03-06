#ifndef _PRIMS_INC_ASSERT_H_
#define _PRIMS_INC_ASSERT_H_

#include <errno.h>

#define OPR_DEFS
#define OPT_DEFS
#define RES_DEFS
#include "common/defs/inc.h"


#define assert(exp1_)               (exp1_)                         ? B_True : B_False
#define assert_eq(exp1_, exp2_)     (exp1_ IS_EQ exp2_)             ? B_True : B_False
#define assert_ne(exp1_, exp2_)     (exp1_ IS_EQ exp2_)             ? B_False; : B_True
#define assert_be(exp1_, exp2_)     (exp1_ IS_BIGGER_OR_EQ  exp2_)  ? B_True; : B_False
#define assert_le(exp1_, exp2_)     (exp1_ IS_SMALLER_OR_EQ exp2_)  ? B_True; : B_False
#define assert_ez(exp1_)            assert_eq(exp1_, 0)
#define assert_nez(exp1_)           assert_ne(exp1_, 0)
#define assert_bez(exp1_)           assert_be(exp1_, 0)
#define assert_lez(exp1_)           assert_le(exp1_, 0)

#define soft_assert(exp_, msg_, ...)              do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return B_False; } }       while(0)
#define soft_assert_ret(exp_, ret_, msg_, ...)    do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return ret_; } }          while(0)
#define soft_assert_ret_int(exp_, msg_, ...)      do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return -1; } }            while(0)
#define soft_assert_ret_ptr(exp_, msg_, ...)      do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return INVALID_HNDL; } }  while(0)
#define soft_assert_ret_id(exp_, msg_, ...)       do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return INVALID_INDEX; } } while(0)
#define soft_assert_ret_float(exp_, msg_, ...)    do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return (float_t)-1; } }   while(0)
#define soft_assert_ret_void(exp_, msg_, ...)     do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return ; } }              while(0)
#define soft_assert_goto_return(exp_, msg_, ...)   do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); goto RETURN; } }         while(0)

#define soft_assert_wrn(exp_, msg_, ...)              do { if (!(exp_)) { debug_wrn(msg_, ## __VA_ARGS__); } } while(0)
#define soft_assert_inf(exp_, msg_, ...)              do { if (!(exp_)) { debug_inf(msg_, ## __VA_ARGS__); } } while(0)
#define soft_assert_log(exp_, msg_, ...)              do { if (!(exp_)) { debug_log(msg_, ## __VA_ARGS__); } } while(0)

#define soft_assert_break(exp_, msg_, ...)         do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_continue(exp_, msg_, ...)      do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_break_wrn(exp_, msg_, ...)          if (!(exp_)) { debug_wrn(msg_, ## __VA_ARGS__); break;}      while(0)
#define soft_assert_continue_wrn(exp_, msg_, ...)  do { if (!(exp_)) { debug_wrn(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_break_inf(exp_, msg_, ...)     do { if (!(exp_)) { debug_inf(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_continue_inf(exp_, msg_, ...)  do { if (!(exp_)) { debug_inf(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_break_log(exp_, msg_, ...)     do { if (!(exp_)) { debug_log(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_continue_log(exp_, msg_, ...)  do { if (!(exp_)) { debug_log(msg_, ## __VA_ARGS__); continue;} } while(0)



#define soft_assert_res(res_, msg_, ...)           do { if (!is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return B_False; } }                              while(0)
#define soft_assert_res_ret_int(res_, msg_, ...)   do { if (!is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return -1; } }                                 while(0)
#define soft_assert_res_ret_ptr(res_, msg_, ...)   do { if (!is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return INVALID_HNDL; } }                       while(0)
#define soft_assert_res_ret_id(res_, msg_, ...)    do { if (!is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return INVALID_INDEX; } }                         while(0)
#define soft_assert_res_ret_float(res_, msg_, ...) do { if (!is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return (float_t)-1; } }                          while(0)
#define soft_assert_res_ret_void(res_, msg_, ...)  do { if (!is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return ; } }                                   while(0)
#define soft_assert_res_ret_res(res_, msg_, ...)   do { if (!is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return (result_t)err(ek_gen); } }  while(0)
#define soft_assert_res_ret_gen(res_, msg_, ...)   do { if (!is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); return G_NONE;} }                               while(0)

#define soft_assert_res_wrn(exp_, msg_, ...)    do { if (!is_ok(res_)) { debug_wrn(msg_, ## __VA_ARGS__); } } while(0)
#define soft_assert_res_inf(exp_, msg_, ...)    do { if (!is_ok(res_)) { debug_inf(msg_, ## __VA_ARGS__); } } while(0)
#define soft_assert_res_log(exp_, msg_, ...)    do { if (!is_ok(res_)) { debug_log(msg_, ## __VA_ARGS__); } } while(0)

#define soft_assert_res_break(exp_, msg_, ...)        do { if (!is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_res_continue(exp_, msg_, ...)     do { if (!is_ok(res_)) { debug_err(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_res_break_wrn(exp_, msg_, ...)    do { if (!is_ok(res_)) { debug_wrn(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_res_continue_wrn(exp_, msg_, ...) do { if (!is_ok(res_)) { debug_wrn(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_res_break_inf(exp_, msg_, ...)    do { if (!is_ok(res_)) { debug_inf(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_res_continue_inf(exp_, msg_, ...) do { if (!is_ok(res_)) { debug_inf(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_res_break_log(exp_, msg_, ...)    do { if (!is_ok(res_)) { debug_log(msg_, ## __VA_ARGS__); break;} }    while(0)
#define soft_assert_res_continue_log(exp_, msg_, ...) do { if (!is_ok(res_)) { debug_log(msg_, ## __VA_ARGS__); continue;} } while(0)
#define soft_assert_ret_res(expr_, msg_, ...)    do { if (!(expr_)) { debug_err(msg_, ## __VA_ARGS__); return err(ek_gen); } } while(0)



#define soft_assert_opt(opt_, msg_, ...)           do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return B_False; } }                               while(0)
#define soft_assert_opt_ret_int(opt_, msg_, ...)   do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return -1; } }                                    while(0)
#define soft_assert_opt_ret_ptr(opt_, msg_, ...)   do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return INVALID_HNDL; } }                          while(0)
#define soft_assert_opt_ret_id(opt_, msg_, ...)    do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return INVALID_INDEX; } }                            while(0)
#define soft_assert_opt_ret_float(opt_, msg_, ...) do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return (float_t)-1; } }                           while(0)
#define soft_assert_opt_ret_void(opt_, msg_, ...)  do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return ; } }                                      while(0)
#define soft_assert_opt_ret_res(opt_, msg_, ...)   do { if (opt_is_none(opt_)) { debug_err(msg_, ## __VA_ARGS__); return (result_t)err(ek_gen); } }   while(0)
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



#define soft_assert_ret_gen(exp_, msg_, ...)      do { if (!(exp_)) { debug_err(msg_, ## __VA_ARGS__); return G_NONE; } } while(0)

#endif // __PRIMS_INC_ASSERT_H