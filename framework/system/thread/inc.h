/**
 * Copyright (C) 2022 Redwan
 * 
 * This file is part of Owl.
 * 
 * Owl is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Owl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Owl.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _FRAMEWORK_SYSTEM_THREAD_INC_H_
#define _FRAMEWORK_SYSTEM_THREAD_INC_H_

#include <pthread.h>

#include "framework/prims/inc.h"
#include "common/defs/inc.h"


typedef struct {
    gen_t           data;
    pthread_mutex_t mutex;
}
guarded_t;


typedef struct {
    pthread_t       hndle;
    pthread_attr_t  attr;
}
thread_t;


thread_t thread_new();

result_t thread_spawn(
    thread_t*  OUT thread,
    handle_t   IN (*thread_handle) (guarded_t*),
    guarded_t* IN  thread_argument
);

result_t thread_wait(
    thread_t OUT thread
);


guarded_t guarded_new(
    gen_t IN data
);


void_t guarded_change(
    guarded_t* IN guard,
    gen_t      IN data
);


result_t guarded_lock(
    guarded_t* IN guard
);


result_t guarded_unlock(
    guarded_t* IN guard
);


#endif // _FRAMEWORK_SYSTEM_THREAD_INC_H_
