#include "../../headers/timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef struct timeval TimeEval;

typedef struct {
    TimeEval begin;
    TimeEval end;
    Int64   spend;
}
_Timer;


Timer timer_new() {
    _Timer* new_timer = (_Timer*) malloc(sizeof(_Timer));
    soft_assert_ret_ptr(new_timer, "Allocating new timer failed!");

    new_timer->begin = (TimeEval) {0};
    new_timer->end   = (TimeEval) {0};

    return (Timer) new_timer;
}


Void timer_start(Timer timer) {
    _Timer* _timer = (_Timer*) timer;
    Int32 res = gettimeofday(&(_timer->begin), INVALID_HNDL);
}


Void timer_pause(Timer timer) {

    _Timer* _timer = (_Timer*) timer;
    Int32 res = gettimeofday(&(_timer->end), INVALID_HNDL);

    _timer->spend += (_timer->end.tv_sec - _timer->begin.tv_sec);
}


Void timer_stop(Timer timer) {

    _Timer* _timer = (_Timer*) timer;
    Int32 res = gettimeofday(&(_timer->end), INVALID_HNDL);

    _timer->spend += (_timer->end.tv_sec - _timer->begin.tv_sec);
}


Void timer_reset(Timer timer) {

    _Timer* _timer = (_Timer*) timer;
    Int32 res = gettimeofday(&(_timer->end), INVALID_HNDL);

    _timer->begin = (TimeEval) {0};
    _timer->end   = (TimeEval) {0};

    _timer->spend = 0;
}


Void timer_reduce(Timer timer, UInt64 seconds) {
    _Timer* _timer = (_Timer*) timer;
    _timer->spend -= seconds;
}


UInt64 time_get_time(Timer timer) {
    _Timer* _timer = (_Timer*) timer;
    return _timer->end.tv_sec - _timer->begin.tv_sec;
}


UInt64 timer_time_spend(Timer timer) {
    _Timer* _timer = (_Timer*) timer;
    return (UInt64) _timer->spend;
}
