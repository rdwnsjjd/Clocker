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

#include "common/defs/inc.h"
#include "framework/prims/inc.h"

typedef struct {
    u64_t inner;
}
clocker_timer_t;

clocker_timer_t timer_new();

void_t timer_init(
    clocker_timer_t* timer,
    u64_t            time, 
    u64_t            spent
);

void_t timer_start(clocker_timer_t* timer);

void_t timer_pause(clocker_timer_t* timer);

void_t timer_resume(clocker_timer_t* timer);

void_t timer_stop(clocker_timer_t* timer);

void_t timer_reset(clocker_timer_t* timer);

void_t timer_reduce(clocker_timer_t* timer, u64_t seconds);

u64_t timer_get_time(clocker_timer_t* timer);

u64_t timer_time_spend(clocker_timer_t* timer);

void_t timer_destroy(clocker_timer_t timer);

#endif // HEADERS_TIMER_H