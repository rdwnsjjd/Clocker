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

#ifndef _HEADERS_THREAD_ARG_H_
#define _HEADERS_THREAD_ARG_H_

#include "../includes/common/inc.h"
#include "mutexed.h"
#include "data_master.h"


typedef enum {
    TM_Default,
    TM_Busy,
    TM_Paused
}
TimeMode;

typedef enum {
    TC_None,
    TC_End,
    TC_Report,
    TC_Pause,
    TC_Resume,
    TC_Save
}
TimeCommand;

typedef struct {
    DataMaster master;
    Str        version;
    Mutexed*   mode;
    Mutexed*   command;
}
TreadArg;


INLINE Str time_mode_from(TimeMode mode) {
    switch (mode) {
        case TM_Default:
            return "default";

        case TM_Busy:
            return "busy";

        case TM_Paused:
            return "paused";
        
        default:
            return "";
    }
}

#endif // _HEADERS_THREAD_ARG_H_
