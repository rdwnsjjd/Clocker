// Copyright (C) 2022 Redwan
// 
// This file is part of Owl.
// 
// Owl is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Owl is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Owl.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _INC_DEFS_COLOR_DEFS_H_
#define _INC_DEFS_COLOR_DEFS_H_

#define COLOR_WHITE       "\x1b[0m"
#define COLOR_BOLD        "\x1b[1m"
#define COLOR_TRANSPARENT "\x1b[2m"
#define COLOR_ITALIC      "\x1b[3m"
#define COLOR_UNDERLINE   "\x1b[4m"
#define COLOR_BLIND       "\x1b[5m"

#define COLOR_IN_RED     "\x1b[41m"
#define COLOR_IN_GREEN   "\x1b[41m"
#define COLOR_IN_YELLOW  "\x1b[43m"
#define COLOR_IN_BLUE    "\x1b[44m"

#define COLOR_BLACK   "\x1b[30m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

#define COLOR_B_RED     "\x1b[91m"
#define COLOR_B_GREEN   "\x1b[92m"
#define COLOR_B_YELLOW  "\x1b[93m"
#define COLOR_B_BLUE    "\x1b[94m"
#define COLOR_B_CYAN    "\x1b[96m"

#define ERR_TXT(txt_)           COLOR_RED          txt_ COLOR_RESET 
#define WRN_TXT(txt_)           COLOR_YELLOW       txt_ COLOR_RESET 
#define OK_TXT(txt_)            COLOR_GREEN        txt_ COLOR_RESET
#define INF_TXT(txt_)           COLOR_B_CYAN       txt_ COLOR_RESET

#define DNG_TXT(txt_)           COLOR_B_RED          txt_ COLOR_RESET 
#define ATT_TXT(txt_)           COLOR_B_YELLOW       txt_ COLOR_RESET 

#define TRANSPARENT_TXT(txt_)   COLOR_TRANSPARENT  txt_ COLOR_RESET
#define BOLD_TXT(txt_)          COLOR_BOLD         txt_ COLOR_RESET
#define UNDER_TXT(txt_)         COLOR_UNDERLINE    txt_ COLOR_RESET
#define ITALIC_TXT(txt_)        COLOR_ITALIC       txt_ COLOR_RESET

#endif // _INC_DEFS_COLOR_DEFS_H_
