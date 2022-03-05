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

#include <stdio.h>

#include "inc.h"


thread_t thread_new() {
    return (thread_t) {
        .attr  = 0,
        .hndle = 0
    };
}


result_t thread_spawn(
    thread_t*  OUT thread,
    handle_t   IN (*thread_handle) (guarded_t*),
    guarded_t* IN  thread_argument
) {
    soft_assert_ret_res(
        thread IS_NOT_EQ INVALID_HNDL,
        "Invalid argument (thread object is null)!"
    );

    handle_t (*pthread_handle) (handle_t) = (handle_t(*) (handle_t)) (*thread_handle);

    soft_assert_ret_res(
        thread_handle IS_NOT_EQ INVALID_HNDL,
        "Invalid argument (thread object is null)!"
    );

    soft_assert_ret(
        pthread_create(&(thread->hndle), INVALID_HNDL, pthread_handle, thread_argument) IS_EQ 0,
        err(ek_createf),
        "Creating new thread failed (os error: %s)!",
        strerror(errno)
    );

    return ok(G_NONE);
}


result_t thread_wait(
    thread_t OUT thread
) {
    pthread_join(thread.hndle, INVALID_HNDL);
}


result_t thread_destroy(
    thread_t OUT thread
) {
    pthread_detach(thread.hndle);
}