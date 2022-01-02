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

#ifndef HEADERS_TIMER_H
#define HEADERS_TIMER_H

#include "../includes/common/inc.h"

typedef UInt64 Timer;


Timer timer_new();

Timer timer_init(UInt64 time, UInt64 spent);

Void timer_start(Timer timer);

Void timer_pause(Timer timer);

Void timer_resume(Timer timer);

Void timer_stop(Timer timer);

Void timer_reset(Timer timer);

Void timer_reduce(Timer timer, UInt64 seconds);

UInt64 timer_get_time(Timer timer);

UInt64 timer_time_spend(Timer timer);

Void timer_destroy(Timer timer);

#endif // HEADERS_TIMER_H