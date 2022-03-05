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

#ifndef _FRAMEWORK_SYSTEM_MEMORY_INC_H_
#define _FRAMEWORK_SYSTEM_MEMORY_INC_H_

#include "framework/prims/inc.h"
#include "common/defs/inc.h"

typedef struct {
    handle_t inner;
}
boxed_t;


boxed_t boxed_new(size_t size);

boxed_t boxed_zeroed_new(size_t n_memb, size_t size);

boxed_t boxed_resize(boxed_t boxed, size_t size);

handle_t boxed_unbox(boxed_t* boxed);

void_t boxed_destroy(boxed_t boxed);

#endif // _FRAMEWORK_SYSTEM_MEMORY_INC_H_
