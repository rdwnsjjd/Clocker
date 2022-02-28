/**
 * Copyright (C) 2021 rdwn
 * 
 * This file is part of Clocker.
 * 
 * Clocker is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Clocker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Clocker.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include "includes/sig_handler.h"


void_t signal_handler(i32_t signal) {

    switch (signal) {

        case SIGINT:
            break;

        case SIGSEGV:
            printf(ERR_TXT("\n\nSignal 11 (SEGV) was caught by Clocker,\n") \
	                "Please send bug reports to <rdwnsjjd@gmail.org>\n");
            _exit(-1);
        default:
            break;
    }
}