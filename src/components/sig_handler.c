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
#include "../../headers/sig_handler.h"


Sig sig_handler(Int32 signal) {

    switch (signal) {

        case SIGINT:

            // printf(COLOR_YELLOW"\nYou are about exiting app. All times will be lost. "COLOR_RESET COLOR_BOLD"Are you sure?[y/N]"COLOR_RESET);
            // Char input_int = fgetc(stdin);fgetc(stdin);

            // if (input_int == 'y' || input_int == 'Y') {
            //     _exit(1);
            // }
            // printf("\n\n> ");
            break;

        case SIGSEGV:
            printf(COLOR_RED"\n\nSignal 11 (SEGV) was caught by Clocker,\n"COLOR_RESET \
	                "Please send bug reports to <rdwnsjjd@gmail.org>\n");
            _exit(-1);
        default:
            break;
    }
}