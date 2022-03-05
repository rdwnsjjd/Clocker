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

#include "common/defs/program_defs.h"
#include "common/defs/basic_defs.h"
#include "framework/system/thread/inc.h"
#include "includes/thread_arg.h"
#include "includes/time_handler.h"
#include "includes/updater_checker.h"
#include "includes/sig_handler.h"
#include "includes/data_manager.h"
#include "includes/cmd.h"


void_t clocker_update_checking(updater_t* checker) {

    // check for update
    update_status_t update_check_res = update_checker_check(checker);
    soft_assert_wrn(
        update_check_res != US_Error,
        "Checking for new version failed!"
    );

    // if update is available, prepare it
    if (update_check_res == US_Updatable) {

        // first, ask user if he/she wants to update app?
        printf("Version %s is available!\nyou have version %s!\nDo you want to install it? [Y/n]", 
            update_checker_get_new_tag(checker),
            update_checker_get_version(checker)
        );

        // getting user response to above question
        char_t result = fgetc(stdin);
        if (result == '\n' || result == 'Y' || result == 'y') {

            // if YES, do update
            str_t arg[3] = {"/usr/bin/clocker-updater", "--from-clocker", INVALID_HNDL};
            execvp("/usr/bin/clocker-updater", arg);
            perror("");
        }
        else {
            // if NO, abort updating process
            printf("Aborted!\n\n");
        }
    }

    // if update is not available, tell it to the user
    else if (update_check_res == US_NoUpdate) {
        printf("All is up to date!\n");
    }
}


result_t clear_cache() {
    printf(INF_TXT("\n Cleaning cash ..."));
    soft_assert_ret_res(
        remove("/root/.config/clocker/lock") == 0,
        "Removing lock file failed: (%s)!",
        strerror(errno)
    );
    // soft_assert_ret_res(
    //     remove("/root/.config/clocker/data") == 0,
    //     "Removing data file failed: (%s)!",
    //     strerror(errno)
    // );
    printf(INF_TXT("\n Done!\n\n"));
}


i32_t main(
    i32_t argc,
    str_t argv[]
) {

    // no_save flag determine if user wants to save its data on system for later use or not
    bool_t no_save = argv[1] && strcmp(argv[1], "--no-save") == 0 ? B_True : B_False;

    // if `--clean` flag used, clear the cash and lock file
    if (argv[1] && strcmp(argv[1], "--clean") == 0) {
        soft_assert_res_ret_int(clear_cache(), "Failed to clear cache!");
    }

    // create new update checker object and check if it sucessfully created
    updater_t checker = update_checker_new();
    soft_assert_wrn(boxed_unbox(&checker.inner) != 0, "Creating new update object failed!");

    // if `--update` flag is used, check for update and do it if availabe
    if (argv[1] && strcmp(argv[1], "--update") == 0) {
        clocker_update_checking(&checker);
    }

    // start data manager and check if it fully started
    data_manager_t manager = data_manager_start(no_save);
    soft_assert_ret_int(boxed_unbox(&manager.inner) != INVALID_HNDL, "Failed to starting data manager!");

    // handle `SIGINT` and `SIGSEGV` signals
    signal(SIGINT, signal_handler);
    signal(SIGSEGV, signal_handler);

    // print app banner and some helpful messages
    printf("%s\n\n", CLOCKER_BANNER);
    printf("Type "ITALIC_TXT("`help`")" to list supported commands\n");

    // creating new thread argument for sending to `time_handle` thread 
    thread_arg_t thread_arg = thread_arg_new(TC_None, TM_Default, update_checker_get_version(&checker), manager);
    guarded_t thread_arg_guarded = guarded_new(_((handle_t) &thread_arg));

    // spawing time handling thread
    thread_t timer_thread = thread_new();
    thread_spawn(&timer_thread, &time_handle, &thread_arg_guarded);

    // spawing command handling thread
    thread_t cmd_thread = thread_new();
    thread_spawn(&cmd_thread, &cmd_run, &thread_arg_guarded);

    // waiting for time thread to join
    thread_wait(timer_thread);

    // destroy another thread
    thread_destroy(cmd_thread);

    // destroy update checker after `timer_thread` joined
    update_checker_destroy(checker);
}
