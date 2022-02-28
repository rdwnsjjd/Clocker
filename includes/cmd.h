// Copyright (C) 2021 root
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

#ifndef _INCLUDES_CMD_H_
#define _INCLUDES_CMD_H_

#include "common/defs/inc.h"
#include "framework/system/thread/inc.h"

handle_t cmd_run(guarded_t* state);

#endif // _INCLUDES_CMD_H_
