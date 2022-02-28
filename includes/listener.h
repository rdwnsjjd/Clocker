// Copyright (C) 2021 rdwn
// 
// This file is part of Clocker.
// 
// Clocker is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Clocker is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Clocker.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADERS_LISTENER_H
#define HEADERS_LISTENER_H

#include "common/defs/inc.h"

typedef struct {
    u64_t inner;
}
listener_t;


listener_t listener_new();

void_t listener_listen(listener_t* listener);

i64_t listener_fired(listener_t* listener);

i64_t listener_drop(listener_t listener);



#define listener_event_fired(_listener) listener_fired(_listener)

#endif // HEADERS_LISTENER_H