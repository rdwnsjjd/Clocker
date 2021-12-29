#ifndef HEADERS_TIMER_H
#define HEADERS_TIMER_H

#include "../includes/common/inc.h"

typedef UInt64 Timer;


Timer timer_new();

Void timer_start(Timer timer);

Void timer_pause(Timer timer);

Void timer_stop(Timer timer);

Void timer_reset(Timer timer);

Void timer_reduce(Timer timer, UInt64 seconds);

UInt64 time_get_time(Timer timer);

UInt64 timer_time_spend(Timer timer);

#endif // HEADERS_TIMER_H