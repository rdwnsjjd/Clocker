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

#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "../common/info.h"
#include "../includes/common/inc.h"
#include "../headers/time_handler.h"
#include "../headers/mutexed.h"
#include "../headers/updater_checker.h"
#include "../headers/sig_handler.h"
#include "../headers/cmd.h"

typedef pthread_t       Thread;


Void clocker_update_checking() {
    Updater checker = update_checker_new();
    soft_assert_wrn(
        checker != 0,
        "Creating new update object failed!"
    );

    UpdateStatus update_check_res = update_checker_check(checker);
    soft_assert_wrn(
        update_check_res != US_Error,
        "Checking for new version failed!"
    );

    if (update_check_res == US_Updatable) {
        printf("Version %s is available!\nyou have version %s!\nDo you want to install it? [Y/n]", 
            update_checker_get_new_tag(checker),
            update_checker_get_version(checker)
        );

        Char result = fgetc(stdin);
        if (result == '\n' || result == 'Y' || result == 'y') {
            Str arg[2] = {"/root/.clocker/clocker-updater", INVALID_HNDL};
            execvp("/root/.clocker/clocker-updater", arg);
            perror("");
        }
        else {
            printf("Aborted!\n\n");
        }
    }
    else if (update_check_res == US_NoUpdate) {
        printf("All is up to date!\n");
    }
}


Int32 main(
    Int32 argc,
    Str   argv[]
) {

    // signal handling
    signal(SIGINT, sig_handler);
    signal(SIGSEGV, sig_handler);

    if (argv[1] && strcmp(argv[1], "--update") == 0) {
        clocker_update_checking();
    }

    printf("%s\n\n", clocker_banner);
    printf("Type "COLOR_ITALIC"`help`"COLOR_RESET" to list supported commands\n");

    Mutexed* state = mutexed_new(gen_type(0));
    soft_assert_ret_int(state != INVALID_HNDL, "Failed to create new mutexed!");

    // creating time handling thread
    Thread timer_thread = 0;
    pthread_create(
        &timer_thread, 
        INVALID_HNDL, 
        time_handle, 
        (Hndl) state
    );

    // creating cmd handling thread
    Thread cmd_thread = 0;
    pthread_create(
        &cmd_thread, 
        INVALID_HNDL, 
        cmd_run, 
        (Hndl) state
    );

    // waiting for time thread
    pthread_join(timer_thread, INVALID_HNDL);
}
