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

#include "../../common/defs.h"
#include "../../headers/cmd.h"
#include "../../headers/thread_arg.h"


Hndl cmd_run(Hndl arg) {

    TreadArg* cmd_arg = (TreadArg*) arg;
    Mutexed*  command = cmd_arg->command;
    Mutexed*  mode    = cmd_arg->mode;
    Str       version = cmd_arg->version;

    Str mode_str = "default";
    loop {

        mode_str = time_mode_from((TimeMode) mode->inner.i64);
        printf(TRANSPARENT_TXT("%s")" > ", mode_str);

        Char input[1024] = {0};
        fgets(input, 1024, stdin);
        if (*input == '\n') {
            continue;
        }
        

        if ((input[0] == 'e' && input[1] == 'n' && input[2] == 'd') || (input[0] == 'E' && input[1] == '\n')) {
            mutexed_change(command, gen_type(TC_End));
            break;
        }

        else if (strcmp(input, "busy\n") == 0 || (input[0] == 'b' && input[1] == '\n')) {

            printf(OK_TXT(" Changed to busy mode.\n"));
            mutexed_change(mode, gen_type(TM_Busy));
        }

        else if (strcmp(input, "default\n") == 0 || (input[0] == 'd' && input[1] == '\n')) {

            printf(OK_TXT(" Changed to default mode.\n"));
            mutexed_change(mode, gen_type(TM_Default));
        }

        else if (strcmp(input, "report\n") == 0 || (input[0] == 'r' && input[1] == '\n')) {
            mutexed_change(command, gen_type(TC_Report));
            sleep(1);
        }

        else if (strcmp(input, "pause\n") == 0 || (input[0] == 'P' && input[1] == '\n')) {

            printf(WRN_TXT(" WARNING: You are using unstable feature\n"));
            
            mutexed_change(command, gen_type(TC_Pause));
            mutexed_change(mode,    gen_type(TM_Paused));
        }

        else if (strcmp(input, "resume\n") == 0 ||  (input[0] == 'R' && input[1] == '\n')) {

            if (mode->inner.i64 != TM_Paused) {
                printf(ERR_TXT(" Not paused mode!\n"));
            }
            

            mutexed_change(command, gen_type(TC_Resume));
            mutexed_change(mode,    gen_type(TM_Default));
        }

        else if (strcmp(input, "version\n") == 0 ||  (input[0] == 'v' && input[1] == '\n')) {
            printf("\n Clocker (%s)\n"\
                TRANSPARENT_TXT("   Copyright (C) 2021 Redwan\n"\
                    "   This is free software; see the source for copying conditions.\n"\
                    "   There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n"
                ),
                version
            );
        }

        else if (strcmp(input, "help\n") == 0 ||  (input[0] == 'h' && input[1] == '\n')) {
            printf("\n Clocker supports these commands:\n" \
                TRANSPARENT_TXT(BOLD_TXT("    b, busy            "))\
                TRANSPARENT_TXT(ITALIC_TXT( ":I have no waste time, even when idel!\n"))\
                TRANSPARENT_TXT(BOLD_TXT("    d, default         "))\
                TRANSPARENT_TXT(ITALIC_TXT(":Oh, I have some waste time, please cosider it!\n"))\
                TRANSPARENT_TXT(BOLD_TXT("    r, report          "))\
                TRANSPARENT_TXT(ITALIC_TXT(":Get me my time to here\n"))\
                TRANSPARENT_TXT(BOLD_TXT("    P, pause           "))\
                TRANSPARENT_TXT(ITALIC_TXT(":Consider all times from now as waste ") WRN_TXT("(UNSTABLE)\n" ))\
                TRANSPARENT_TXT(BOLD_TXT("    R, resume          "))\
                TRANSPARENT_TXT(ITALIC_TXT(":Resume paused mode\n"))\
                TRANSPARENT_TXT(BOLD_TXT("    v, version         "))\
                TRANSPARENT_TXT(ITALIC_TXT(":Get app version \n"))\
                TRANSPARENT_TXT(BOLD_TXT("    E, end             "))\
                TRANSPARENT_TXT(ITALIC_TXT(":End the program and get final report\n\n"))
            );
        }
        
        else {
            printf(WRN_TXT(" Invalid command!\n"));
        }
    }

}