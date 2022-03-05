/**
 * Copyright (C) 2021 rdwn
 * 
 * This file is part of Clocker.
 * 
 * Clocker is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Clocker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Clocker.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "includes/timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef struct timeval time_eval_t;

typedef struct {
    time_eval_t begin;
    time_eval_t end;
    i64_t       spend;
    i64_t       total_offset;
    i64_t       spend_offset;
}
_clocker_timer_t;


clocker_timer_t timer_new() {
    boxed_t boxed = boxed_new(sizeof(_clocker_timer_t));
    soft_assert_ret(boxed_unbox(&boxed) != INVALID_HNDL, (clocker_timer_t) {.inner = INVALID_HNDL},  "Creating new timer pointer boxed failed!");

    _clocker_timer_t* new_timer = (_clocker_timer_t*) boxed_unbox(&boxed);

    new_timer->begin  = (time_eval_t) {0};
    new_timer->end    = (time_eval_t) {0};
    new_timer->spend  = 0;

    new_timer->total_offset = 0;
    new_timer->spend_offset = 0;

    return (clocker_timer_t) {
        .inner = boxed
    };
}


void_t timer_init(clocker_timer_t* timer, u64_t time, u64_t spent) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) boxed_unbox(&timer->inner);
    _timer->total_offset = time;
    _timer->spend_offset = spent;
}


void_t timer_start(clocker_timer_t* timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) boxed_unbox(&timer->inner);
    
    if (_timer->begin.tv_sec == 0) {
        gettimeofday(&(_timer->begin), INVALID_HNDL);
        _timer->begin.tv_sec -= _timer->total_offset;
    }

    return;
}


void_t timer_pause(clocker_timer_t* timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) boxed_unbox(&timer->inner);
    i32_t res = gettimeofday(&(_timer->end), INVALID_HNDL);
    _timer->spend += (_timer->end.tv_sec - _timer->begin.tv_sec);
}


void_t timer_resume(clocker_timer_t* timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) boxed_unbox(&timer->inner);
    _timer->spend -= (_timer->end.tv_sec - _timer->begin.tv_sec);
}


void_t timer_stop(clocker_timer_t* timer) {
    timer_pause(timer);
}


void_t timer_reset(clocker_timer_t* timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) boxed_unbox(&timer->inner);
    // i32_t res = gettimeofday(&(_timer->end), INVALID_HNDL);

    _timer->begin = (time_eval_t) {0};
    _timer->end   = (time_eval_t) {0};
    
    _timer->spend_offset = 0;
    _timer->total_offset = 0;

    _timer->spend = 0;
}


void_t timer_reduce(clocker_timer_t* timer, u64_t seconds) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) boxed_unbox(&timer->inner);
    _timer->spend -= seconds;
}


u64_t timer_get_time(clocker_timer_t* timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) boxed_unbox(&timer->inner);
    return (_timer->end.tv_sec - _timer->begin.tv_sec);
}


u64_t timer_time_spend(clocker_timer_t* timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) boxed_unbox(&timer->inner);
    return (u64_t) _timer->spend + _timer->spend_offset - _timer->total_offset;
}


void_t timer_destroy(clocker_timer_t timer) {
    boxed_destroy(timer.inner);
}