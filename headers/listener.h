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

#include "../includes/common/inc.h"
#include "../common/defs.h"

typedef UInt64 Listener;


Listener listener_new();

Void listener_listen(Listener listener);

Int64 listener_fired(Listener listener);



#define listener_event_fired(_listener) listener_fired(_listener)

#endif // HEADERS_LISTENER_H