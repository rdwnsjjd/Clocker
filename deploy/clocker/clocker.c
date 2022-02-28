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
#include "includes/data_master.h"
#include "includes/cmd.h"


// void_t clocker_update_checking(updater_t checker) {

//     update_status_t update_check_res = update_checker_check(checker);
//     soft_assert_wrn(
//         update_check_res != US_Error,
//         "Checking for new version failed!"
//     );

//     if (update_check_res == US_Updatable) {
//         printf("Version %s is available!\nyou have version %s!\nDo you want to install it? [Y/n]", 
//             update_checker_get_new_tag(checker),
//             update_checker_get_version(checker)
//         );

//         char_t result = fgetc(stdin);
//         if (result == '\n' || result == 'Y' || result == 'y') {
//             str_t arg[3] = {"/usr/bin/clocker-updater", "--from-clocker", INVALID_HNDL};
//             execvp("/usr/bin/clocker-updater", arg);
//             perror("");
//         }
//         else {
//             printf("Aborted!\n\n");
//         }
//     }
//     else if (update_check_res == US_NoUpdate) {
//         printf("All is up to date!\n");
//     }
// }


i32_t main(
    i32_t argc,
    str_t   argv[]
) {

    // bool_t no_save = B_False;
    // if (argv[1] && strcmp(argv[1], "--no-save") == 0) {

    //     no_save = B_True;
    // }

    // if (argv[1] && strcmp(argv[1], "--clean") == 0) {

    //     printf(INF_TXT("\n Cleaning cash ..."));
    //     soft_assert_ret_int(
    //         remove("/root/.config/clocker/lock") == 0,
    //         "Removing lock file failed: (%s)!",
    //         strerror(errno)
    //     );
    //     printf(INF_TXT("\n Done!"));
    // }

    data_master_t master = data_master_on(B_True /* no_save */);
    soft_assert_ret_int(master.inner != 0, "Failed to turning data master on!");

    // if (argv[1] && strcmp(argv[1], "--clean") == 0) {

    //     data_master_unlock();
    // }

    // signal handling
    signal(SIGINT, signal_handler);
    signal(SIGSEGV, signal_handler);


    // updater_t checker = update_checker_new();
    // soft_assert_wrn(
    //     checker != 0,
    //     "Creating new update object failed!"
    // );

    // if (argv[1] && strcmp(argv[1], "--update") == 0) {
    //     clocker_update_checking(checker);
    // }


    printf("%s\n\n", CLOCKER_BANNER);
    printf("Type "ITALIC_TXT("`help`")" to list supported commands\n");

    thread_arg_t thread_arg = thread_arg_new(TC_None, TM_Default, "0.3.0-beta", master); // update_checker_get_version(checker)
    guarded_t thread_arg_guarded = guarded_new(_((handle_t) &thread_arg));

    // creating time handling thread
    thread_t timer_thread = thread_new();
    thread_spawn(&timer_thread, &time_handle, &thread_arg_guarded);

    // creating cmd handling thread
    thread_t cmd_thread = thread_new();
    thread_spawn(&timer_thread, &cmd_run, &thread_arg_guarded);

    // waiting for time thread
    thread_wait(timer_thread);
}
