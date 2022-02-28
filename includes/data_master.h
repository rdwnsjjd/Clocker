// Copyright (C) 2022 Redwan
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

#ifndef _INCLUDES_DATA_MASTER_H_
#define _INCLUDES_DATA_MASTER_H_

#include "common/defs/inc.h"
#include "framework/prims/inc.h"
#include "includes/timer.h"

typedef struct {
    u64_t inner;
}
data_master_t;

bool_t data_master_save_data(
    data_master_t*   master, 
    clocker_timer_t* timer, 
    bool_t           final
);

data_master_t data_master_on(bool_t no_save);

void_t data_master_off(data_master_t master, clocker_timer_t* timer);

clocker_timer_t data_master_get_timer(data_master_t* master);

bool_t data_master_allow_saving(data_master_t* master);

#endif // _INCLUDES_DATA_MASTER_H_
