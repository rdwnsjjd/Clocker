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

#include "../common/defs.h"
#include "../includes/common/inc.h"
#include "time_handler.h"
#include "mutexed.h"
#include "updater_checker.h"
#include "sig_handler.h"
#include "data_master.h"
#include "cmd.h"

typedef pthread_t Thread;


Void clocker_update_checking(Updater checker) {

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
            Str arg[3] = {"/usr/bin/clocker-updater", "--from-clocker", INVALID_HNDL};
            execvp("/usr/bin/clocker-updater", arg);
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

    Bool no_save = True;
    if (argv[1] && strcmp(argv[1], "--save") == 0) {

        printf(WRN_TXT("\n WARNING: you are using UNSTABLE feature!\n"\
                "   You may face some unknown behavior or crash in app.\n"\
                "   This feature is just for testing no for normal usage.\n"
                "   If you face any problem, contact me\n\n"));

        no_save = False;
    }

    DataMaster master = data_master_on(no_save);
    soft_assert_ret_int(master != 0, "Failed to turning data master on!");

    if (argv[1] && strcmp(argv[1], "--clean") == 0) {

        data_master_unlock();
    }

    // signal handling
    signal(SIGINT, signal_handler);
    signal(SIGSEGV, signal_handler);


    Updater checker = update_checker_new();
    soft_assert_wrn(
        checker != 0,
        "Creating new update object failed!"
    );

    if (argv[1] && strcmp(argv[1], "--update") == 0) {
        clocker_update_checking(checker);
    }


    printf("%s\n\n", CLOCKER_BANNER);
    printf("Type "ITALIC_TXT("`help`")" to list supported commands\n");

    TreadArg thread_arg = (TreadArg) {
        .command = mutexed_new(gen_type(TC_None)),
        .mode    = mutexed_new(gen_type(TM_Default)),
        .version = update_checker_get_version(checker),
        .master  = master
    };
    soft_assert_ret_int(thread_arg.command != INVALID_HNDL, "Failed to create new mutexed!");
    soft_assert_ret_int(thread_arg.mode    != INVALID_HNDL, "Failed to create new mutexed!");


    // creating time handling thread
    Thread timer_thread = 0;
    pthread_create(
        &timer_thread, 
        INVALID_HNDL, 
        time_handle, 
        (Hndl) &thread_arg
    );

    // creating cmd handling thread
    Thread cmd_thread = 0;
    pthread_create(
        &cmd_thread, 
        INVALID_HNDL, 
        cmd_run, 
        (Hndl) &thread_arg
    );

    // waiting for time thread
    pthread_join(timer_thread, INVALID_HNDL);
}
