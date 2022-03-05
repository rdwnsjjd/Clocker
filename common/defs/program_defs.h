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

#ifndef _COMMON_DEFS_PROGRAM_DEFS_H_
#define _COMMON_DEFS_PROGRAM_DEFS_H_

#include "common/defs/inc.h"

#define INIT_VERSION "0.5-beta.0"

#define CLOCKER_BANNER  COLOR_TRANSPARENT"\n"\
"   █████████  ████                    █████\n" \
"  ███░░░░░███░░███                   ░░███\n" \
" ███     ░░░  ░███   ██████   ██████  ░███ █████  ██████  ████████\n" \
"░███          ░███  ███░░███ ███░░███ ░███░░███  ███░░███░░███░░███\n" \
"░███          ░███ ░███ ░███░███ ░░░  ░██████░  ░███████  ░███ ░░░\n" \
"░░███     ███ ░███ ░███ ░███░███  ███ ░███░░███ ░███░░░   ░███\n" \
" ░░█████████  █████░░██████ ░░██████  ████ █████░░██████  █████\n" \
"  ░░░░░░░░░  ░░░░░  ░░░░░░   ░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░\n"COLOR_RESET


#define ERR_TXT(txt_)           COLOR_RED          txt_ COLOR_RESET 
#define WRN_TXT(txt_)           COLOR_YELLOW       txt_ COLOR_RESET 
#define OK_TXT(txt_)            COLOR_GREEN        txt_ COLOR_RESET
#define INF_TXT(txt_)           COLOR_B_CYAN         txt_ COLOR_RESET

#define DNG_TXT(txt_)           COLOR_B_RED          txt_ COLOR_RESET 
#define ATT_TXT(txt_)           COLOR_B_YELLOW       txt_ COLOR_RESET 

#define TRANSPARENT_TXT(txt_)   COLOR_TRANSPARENT  txt_ COLOR_RESET
#define BOLD_TXT(txt_)          COLOR_BOLD         txt_ COLOR_RESET
#define ITALIC_TXT(txt_)        COLOR_ITALIC       txt_ COLOR_RESET

#endif // _COMMON_DEFS_PROGRAM_DEFS_H_
