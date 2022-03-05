/**
 * Copyright (C) 2022 Redwan
 * 
 * This file is part of clocker-safe.
 * 
 * clocker-safe is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * clocker-safe is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with clocker-safe.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include "inc.h"

boxed_t boxed_new(size_t size) {
    handle_t inner = malloc(size);
    soft_assert_ret(inner != INVALID_HNDL, (boxed_t) {.inner = INVALID_HNDL}, "Allocating new boxed pointer failed!");
    return (boxed_t) {.inner = inner};
}

boxed_t boxed_zeroed_new(size_t n_memb, size_t size) {
    handle_t inner = calloc(n_memb, size);
    soft_assert_ret(inner != INVALID_HNDL, (boxed_t) {.inner = INVALID_HNDL}, "Allocating new boxed pointer failed!");
    return (boxed_t) {.inner = inner};
}

boxed_t boxed_resize(boxed_t boxed, size_t size) {
    debug_err("`boxed_resize` is not implemented yet!");
    return (boxed_t) {.inner = INVALID_HNDL};
}

handle_t boxed_unbox(boxed_t* boxed) {
    return boxed->inner;
}

void_t boxed_destroy(boxed_t boxed) {
    free(boxed.inner);
}