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

#ifndef _INCLUDES_THREAD_ARG_H_
#define _INCLUDES_THREAD_ARG_H_

#include "common/defs/inc.h"
#include "framework/system/thread/inc.h"
#include "includes/data_master.h"


typedef enum {
    TM_Default,
    TM_Busy,
    TM_Paused
}
time_mode_t;

typedef enum {
    TC_None,
    TC_End,
    TC_Report,
    TC_Pause,
    TC_Resume,
    TC_Save
}
time_command_t;

typedef struct {
    data_master_t  master;
    str_t          version;
    time_command_t command;
    time_mode_t    mode;
}
thread_arg_t;


INLINE thread_arg_t thread_arg_new(
    time_command_t command, 
    time_mode_t    mode, 
    str_t          version, 
    data_master_t  master
) {
    return (thread_arg_t) {
        .command = command,
        .mode    = mode,
        .version = version,
        .master  = master
    };
}


INLINE str_t time_mode_from(time_mode_t mode) {
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

#endif // _INCLUDES_THREAD_ARG_H_
