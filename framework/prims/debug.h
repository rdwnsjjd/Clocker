#ifndef _PRIMS_INC_DEBUG_H_
#define _PRIMS_INC_DEBUG_H_

#include <stdio.h>
#include <string.h>

#include "common/defs/color_defs.h"

#define __FILENAME__        (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)  

#define ERR_LBL "ERR"
#define WRN_LBL "WRN"
#define INF_LBL "INF"
#define LOG_LBL "LOG"

#ifdef DEBUG
    #define _debug_msg(label_in_color_, label_color_, label_, msg_, ...)   do { printf( "[" BOLD_TXT(label_color_"  %s  ") "]  ", label_); \
                                                                                printf( label_in_color_ msg_, ##__VA_ARGS__);\
                                                                                printf("   " UNDER_TXT( ITALIC_TXT( TRANSPARENT_TXT ( "at: %s %s, %s, fn: %s, ln: %d"))) , __DATE__, __TIME__, __FILENAME__, __func__, __LINE__ ); \
                                                                                printf("\n");\
                                                                            } while(0)
#else 
    #define _debug_msg(label_, msg_, ...)
#endif

// ------------------------------------------------------------------------------------------------------------------------------------------

#define debug_err(msg_, ...)             _debug_msg(COLOR_RED,    COLOR_IN_RED,    ERR_LBL, msg_, ##__VA_ARGS__)
#define debug_wrn(msg_, ...)             _debug_msg(COLOR_YELLOW, COLOR_IN_YELLOW, WRN_LBL, msg_, ##__VA_ARGS__)
#define debug_inf(msg_, ...)             _debug_msg(COLOR_BLUE,   COLOR_IN_BLUE,   INF_LBL, msg_, ##__VA_ARGS__)
#define debug_log(msg_, ...)             _debug_msg(COLOR_BOLD,   COLOR_BOLD,      LOG_LBL, msg_, ##__VA_ARGS__)

#endif // __PRIMS_INC_DEBUG_H