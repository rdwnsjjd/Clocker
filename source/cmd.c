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

#include "common/defs/inc.h"
#include "includes/cmd.h"
#include "includes/thread_arg.h"


handle_t cmd_run(guarded_t* arg) {

    // TODO: thread safe

    thread_arg_t*   cmd_arg   = arg->data.ptr;
    time_command_t* command = &cmd_arg->command;
    time_mode_t*    mode    = &cmd_arg->mode;
    str_t           version   = cmd_arg->version;

    str_t mode_str = "default";
    loop {
        mode_str = time_mode_from((time_mode_t) *mode);
        printf(TRANSPARENT_TXT("%s")" > ", mode_str);

        char_t input[1024] = {0};
        fgets(input, 1024, stdin);
        if (*input == '\n') {
            continue;
        }
        

        if ((input[0] == 'e' && input[1] == 'n' && input[2] == 'd') || (input[0] == 'E' && input[1] == '\n')) {
            *command = TC_End;
            break;
        }

        else if (strcmp(input, "busy\n") == 0 || (input[0] == 'b' && input[1] == '\n')) {

            printf(OK_TXT(" Changed to busy mode\n"));
            *mode = TM_Busy;
        }

        else if (strcmp(input, "default\n") == 0 || (input[0] == 'd' && input[1] == '\n')) {

            printf(OK_TXT(" Changed to default mode\n"));
            *mode = TM_Default;
        }

        else if (strcmp(input, "report\n") == 0 || (input[0] == 'r' && input[1] == '\n')) {
            *command = TC_Report;
            sleep(1);
        }

        else if (strcmp(input, "pause\n") == 0 || (input[0] == 'P' && input[1] == '\n')) {

            *command = TC_Pause;
            *mode    = TM_Paused;
        }

        else if (strcmp(input, "resume\n") == 0 ||  (input[0] == 'R' && input[1] == '\n')) {

            if (*mode != TM_Paused) {
                printf(ERR_TXT(" Not paused mode!\n"));
            }
            

            *command = TC_Resume;
            *mode    = TM_Default;
        }

        else if (strcmp(input, "save\n") == 0 ||  (input[0] == 'S' && input[1] == '\n')) {
            printf(ERR_TXT(" Not for use yet!\n"));
            // guarded_change(command, _(TC_Save));
        }

        else if (strcmp(input, "clear\n") == 0 ||  (input[0] == 'C' && input[1] == '\n')) {
            printf("\e[1;1H\e[2J");
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
                TRANSPARENT_TXT(ITALIC_TXT( ":I have no waste time, even when idle!\n"))\
                TRANSPARENT_TXT(BOLD_TXT("    d, default         "))\
                TRANSPARENT_TXT(ITALIC_TXT(":Oh, I have some waste time, please consider it!\n"))\
                TRANSPARENT_TXT(BOLD_TXT("    r, report          "))\
                TRANSPARENT_TXT(ITALIC_TXT(":Get me my time to here\n"))\
                TRANSPARENT_TXT(BOLD_TXT("    P, pause           "))\
                TRANSPARENT_TXT(ITALIC_TXT(":Consider all times from now as waste \n"))\
                TRANSPARENT_TXT(BOLD_TXT("    R, resume          "))\
                TRANSPARENT_TXT(ITALIC_TXT(":Resume paused mode\n"))\
                TRANSPARENT_TXT(BOLD_TXT("    C, clear           "))\
                TRANSPARENT_TXT(ITALIC_TXT(":Set console offset to the top!\n"))
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

    // guarded_unlock(arg);

}