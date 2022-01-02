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

#ifndef HEADERS_DATA_MASTER_H
#define HEADERS_DATA_MASTER_H

#include "../includes/common/inc.h"
#include "timer.h"

typedef UInt64 DataMaster;

Bool data_master_save_data(
    DataMaster master, 
    Timer     timer, 
    Bool      final
);

DataMaster data_master_on(Bool no_save);

Void data_master_off(DataMaster master, Timer timer);

Timer data_master_get_timer(DataMaster master);

Timer data_master_allow_saving(DataMaster master);

#endif // HEADERS_DATA_MASTER_H