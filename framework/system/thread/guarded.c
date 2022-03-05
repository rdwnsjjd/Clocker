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

#include "inc.h"


guarded_t guarded_new(
    gen_t IN data
) {
    guarded_t guard = {0};
    guard.data      = data;
    
    pthread_mutex_init(&(guard.mutex), INVALID_HNDL);
    return guard;
}


void_t guarded_change(
    guarded_t* IN guard,
    gen_t      IN data
) {
    guard->data = data;
}


result_t guarded_lock(
    guarded_t* IN guard
) {
    pthread_mutex_lock(&(guard->mutex));
    return ok((handle_t) &(guard->data));
}


result_t guarded_unlock(
    guarded_t* IN guard
) {
    pthread_mutex_unlock(&(guard->mutex));
    return ok(guard->data);
}


result_t guarded_serialize(
    guarded_t* IN  gaurd,
    bytes_t    OUT buffer,
    size_t     IN  capacity
) {
    soft_assert_wrn(capacity IS_NOT_EQ 0, "The given buffer capacity is zero!");

    // TODO

    return err(ek_not_impl);
}

// #define GUARD(data_)    guarded_new()