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

#ifndef HEADERS_ENV_H
#define HEADERS_ENV_H

#include "../includes/common/inc.h"
#include "../headers/mutexed.h"

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
    TC_Resume
}
TimeCommand;

typedef struct {
    Str      version;
    Mutexed* mode;
    Mutexed* command;
}
TreadArg;


INLINE Str time_mode_from(TimeMode mode) {
    switch (mode) {
        case TM_Default:
            return "default";

        case TM_Busy:
            return "busy";

        case TM_Paused:
            return WRN_TXT("paused");
        
        default:
            return "";
    }
}

#endif // HEADERS_ENV_H