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

#include "../../headers/mutexed.h"

#include <stdlib.h>

Mutexed* mutexed_new(GenType inner) {

    Mutexed* new = (Mutexed*) malloc(sizeof(Mutexed));
    soft_assert_ret_ptr(new != INVALID_HNDL, "Allocating new mutexed failed!");

    new->mutex = (Mutex) {0};
    new->inner = inner;

    pthread_mutex_init(&new->mutex, INVALID_HNDL);

    return new;
}

Void mutexed_change(Mutexed* mutexed, GenType value) {
    pthread_mutex_lock(&mutexed->mutex);
    mutexed->inner = value;
    pthread_mutex_unlock(&mutexed->mutex);
}

Void mutexed_destroy(Mutexed* mutexed) {
    pthread_mutex_destroy(&mutexed->mutex);
    free(mutexed);
}