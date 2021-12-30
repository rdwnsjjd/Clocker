/**
 * Copyright (C) 2021 root
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

#include "../../headers/cmd.h"
#include "../../headers/mutexed.h"


Hndl cmd_run(Hndl arg) {

    Mutexed* state = (Mutexed*) arg;

    Str state_str = "default";
    loop {

        switch (state->inner.i64) {
        case 0:
            state_str = "default";
            break;

        case 2:
            state_str = "busy";
            break;
        
        default:
            break;
        }

        printf(COLOR_TRANSPARENT"%s"COLOR_RESET" > ", state_str);
        Char input[1024] = {0};

        fgets(input, 1024, stdin);
        if (*input == '\n') {
            continue;
        }
        

        if (input[0] == 'e' && input[1] == 'n' && input[2] == 'd' || input[0] == 'e' && input[1] == '\n') {
            mutexed_change(state, gen_type(1));
            break;
        }

        else if (strcmp(input, "busy\n") == 0 || strcmp(input, "b\n") == 0) {

            if ( strcmp(state_str, input) != 0) {
                printf(COLOR_GREEN"Changed to busy mode.\n"COLOR_RESET);
            }
            else {
                printf(COLOR_TRANSPARENT"Already in busy mode!"COLOR_RESET); 
                continue;
            }

            mutexed_change(state, gen_type(2));
        }

        else if (strcmp(input, "default\n") == 0 || strcmp(input, "d\n") == 0) {

            if ( strcmp(state_str, input) != 0) {
                printf(COLOR_GREEN"Changed to default mode.\n"COLOR_RESET);
            }
            else {
                printf(COLOR_TRANSPARENT"Already in default mode!"COLOR_RESET); 
                continue;
            }

            mutexed_change(state, gen_type(0));
        }

        else if (strcmp(input, "report\n") == 0 || strcmp(input, "r\n") == 0) {
            mutexed_change(state, gen_type(3));
            sleep(1);
        }

        else if (strcmp(input, "help\n") == 0 || strcmp(input, "h\n") == 0) {
            printf("\n Clocker supports these commands:\n"COLOR_TRANSPARENT \
                   COLOR_BOLD"    busy            "COLOR_RESET COLOR_TRANSPARENT COLOR_ITALIC\
                   ":I have no waste time, even when idel!\n"COLOR_RESET COLOR_TRANSPARENT\
                   COLOR_BOLD"    default          "COLOR_RESET COLOR_TRANSPARENT COLOR_ITALIC\
                   ":Oh, I have some waste time, please cosider it!\n"COLOR_RESET COLOR_TRANSPARENT\
                   COLOR_BOLD"    report          "COLOR_RESET COLOR_TRANSPARENT COLOR_ITALIC\
                   ":Get me my time to here "COLOR_YELLOW"(not implemented yet :( )\n"COLOR_RESET COLOR_TRANSPARENT\
                   COLOR_BOLD"    version         "COLOR_RESET COLOR_TRANSPARENT COLOR_ITALIC\
                   ":Get app version "COLOR_YELLOW"(not implemented yet :( )\n"COLOR_RESET COLOR_TRANSPARENT\
                   COLOR_BOLD"    update          "COLOR_RESET COLOR_TRANSPARENT COLOR_ITALIC\
                   ":Check for update!\n\n"COLOR_RESET
            );
        }
        
        else {
            printf(COLOR_YELLOW"Invalid command!\n"COLOR_RESET);
        }
    }

}