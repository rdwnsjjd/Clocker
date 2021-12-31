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

#ifndef __PRIMS_INC_DEBUG_H
#define __PRIMS_INC_DEBUG_H

#include <stdio.h>
#include <string.h>

#define COLOR_BOLD        "\x1b[1m"
#define COLOR_ITALIC      "\x1b[3m"
#define COLOR_UNDERLINE   "\x1b[4m"
#define COLOR_TRANSPARENT "\x1b[2m"

#define COLOR_IN_RED     "\x1b[41m"
#define COLOR_IN_GREEN   "\x1b[41m"
#define COLOR_IN_YELLOW  "\x1b[43m"
#define COLOR_IN_BLUE    "\x1b[44m"

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

#define __FILENAME__        (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)  

#define ERR_LBL "ERR"
#define WRN_LBL "WRN"
#define INF_LBL "INF"
#define LOG_LBL "LOG"

#ifndef DEBUG
    #define _debug_msg(label_in_color_, label_color_, label_, msg_, ...)   do { printf("\n["COLOR_BOLD label_color_"  %s  "COLOR_RESET"]  ", label_);\
                                                                            printf(label_in_color_ msg_ COLOR_RESET, ##__VA_ARGS__);\
                                                                            printf("   "COLOR_UNDERLINE COLOR_ITALIC COLOR_TRANSPARENT"at: %s %s, %s, fn: %s, ln: %d", __DATE__, __TIME__, __FILENAME__, __func__, __LINE__); \
                                                                            printf(COLOR_RESET"\n");} while(0)
#else 
    #define _debug_msg(label_, msg_, ...)
#endif

// ------------------------------------------------------------------------------------------------------------------------------------------

#define debug_err(msg_, ...)             _debug_msg(COLOR_RED,    COLOR_IN_RED,    ERR_LBL, msg_, ##__VA_ARGS__)
#define debug_wrn(msg_, ...)             _debug_msg(COLOR_YELLOW, COLOR_IN_YELLOW, WRN_LBL, msg_, ##__VA_ARGS__)
#define debug_inf(msg_, ...)             _debug_msg(COLOR_BLUE,   COLOR_IN_BLUE,   INF_LBL, msg_, ##__VA_ARGS__)
#define debug_log(msg_, ...)             _debug_msg(COLOR_BOLD,   COLOR_BOLD,      LOG_LBL, msg_, ##__VA_ARGS__)

#endif // __PRIMS_INC_DEBUG_H