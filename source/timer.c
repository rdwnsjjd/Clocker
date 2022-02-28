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
    i64_t    spend;
    i64_t    total_offset;
    i64_t    spend_offset;
}
_clocker_timer_t;


clocker_timer_t timer_new() {
    _clocker_timer_t* new_timer = (_clocker_timer_t*) malloc(sizeof(_clocker_timer_t));
    soft_assert_ret(new_timer != INVALID_HNDL, (clocker_timer_t) {.inner = INVALID_HNDL},  "Allocating new timer failed!");

    new_timer->begin  = (time_eval_t) {0};
    new_timer->end    = (time_eval_t) {0};
    new_timer->spend  = 0;

    new_timer->total_offset = 0;
    new_timer->spend_offset = 0;

    return (clocker_timer_t) {
        .inner = (u64_t) new_timer
    };
}


void_t timer_init(clocker_timer_t* timer, u64_t time, u64_t spent) {
    ((_clocker_timer_t*) timer->inner)->total_offset = time;
    ((_clocker_timer_t*) timer->inner)->spend_offset = spent;
}


void_t timer_start(clocker_timer_t* timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) timer->inner;
    
    if (_timer->begin.tv_sec == 0) {
        gettimeofday(&(_timer->begin), INVALID_HNDL);
        _timer->begin.tv_sec -= _timer->total_offset;
    }

    return;
}


void_t timer_pause(clocker_timer_t* timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) timer->inner;
    i32_t res = gettimeofday(&(_timer->end), INVALID_HNDL);
    _timer->spend += (_timer->end.tv_sec - _timer->begin.tv_sec);
}


void_t timer_resume(clocker_timer_t* timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) timer->inner;
    _timer->spend -= (_timer->end.tv_sec - _timer->begin.tv_sec);
}


void_t timer_stop(clocker_timer_t* timer) {
    timer_pause(timer);
}


void_t timer_reset(clocker_timer_t* timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) timer->inner;
    // i32_t res = gettimeofday(&(_timer->end), INVALID_HNDL);

    _timer->begin = (time_eval_t) {0};
    _timer->end   = (time_eval_t) {0};
    
    _timer->spend_offset = 0;
    _timer->total_offset = 0;

    _timer->spend = 0;
}


void_t timer_reduce(clocker_timer_t* timer, u64_t seconds) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) timer->inner;
    _timer->spend -= seconds;
}


u64_t timer_get_time(clocker_timer_t* timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) timer->inner;
    return (_timer->end.tv_sec - _timer->begin.tv_sec);
}


u64_t timer_time_spend(clocker_timer_t* timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) timer->inner;
    return (u64_t) _timer->spend + _timer->spend_offset - _timer->total_offset;
}


void_t timer_destroy(clocker_timer_t timer) {
    _clocker_timer_t* _timer = (_clocker_timer_t*) timer.inner;
    free(_timer);
}