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

#include "../../headers/timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef struct timeval TimeEval;

typedef struct {
    TimeEval begin;
    TimeEval end;
    Int64    spend;
    Int64    total_offset;
    Int64    spend_offset;
}
_Timer;


Timer timer_new() {
    _Timer* new_timer = (_Timer*) malloc(sizeof(_Timer));
    soft_assert_ret_id(new_timer, "Allocating new timer failed!");

    new_timer->begin  = (TimeEval) {0};
    new_timer->end    = (TimeEval) {0};
    new_timer->spend  = 0;

    new_timer->total_offset = 0;
    new_timer->spend_offset = 0;

    return (Timer) new_timer;
}


Timer timer_init(UInt64 time, UInt64 spent) {
    _Timer* new_timer = (_Timer*) timer_new();
    soft_assert_ret_id(new_timer, "Allocating new timer failed!");

    new_timer->total_offset = time;
    new_timer->spend_offset = spent;

    return (Timer) new_timer;
}


Void timer_start(Timer timer) {
    _Timer* _timer = (_Timer*) timer;
    
    if (_timer->begin.tv_sec == 0) {
        gettimeofday(&(_timer->begin), INVALID_HNDL);
        _timer->begin.tv_sec -= _timer->total_offset;
    }

    return;
}


Void timer_pause(Timer timer) {

    _Timer* _timer = (_Timer*) timer;
    Int32 res = gettimeofday(&(_timer->end), INVALID_HNDL);

    _timer->spend += (_timer->end.tv_sec - _timer->begin.tv_sec);
}


Void timer_resume(Timer timer) {

    _Timer* _timer = (_Timer*) timer;
    _timer->spend -= (_timer->end.tv_sec - _timer->begin.tv_sec);
}


Void timer_stop(Timer timer) {
    timer_pause(timer);
}


Void timer_reset(Timer timer) {

    _Timer* _timer = (_Timer*) timer;
    // Int32 res = gettimeofday(&(_timer->end), INVALID_HNDL);

    _timer->begin = (TimeEval) {0};
    _timer->end   = (TimeEval) {0};
    
    _timer->spend_offset = 0;
    _timer->total_offset = 0;

    _timer->spend = 0;
}


Void timer_reduce(Timer timer, UInt64 seconds) {
    _Timer* _timer = (_Timer*) timer;
    _timer->spend -= seconds;
}


UInt64 timer_get_time(Timer timer) {
    _Timer* _timer = (_Timer*) timer;
    return (_timer->end.tv_sec - _timer->begin.tv_sec);
}


UInt64 timer_time_spend(Timer timer) {
    _Timer* _timer = (_Timer*) timer;
    return (UInt64) _timer->spend + _timer->spend_offset - _timer->total_offset;
}


Void timer_destroy(Timer timer) {
    _Timer* _timer = (_Timer*) timer;

    free(_timer);
}