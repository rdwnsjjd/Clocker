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

#include "includes/time_handler.h"
#include "framework/system/thread/inc.h"
#include "includes/timer.h"
#include "includes/listener.h"
#include "includes/data_master.h"
#include "includes/thread_arg.h"


void_t time_print(clocker_timer_t* main_timer) {

    u64_t total_time       = timer_get_time(main_timer);
    u64_t total_final_time = timer_time_spend(main_timer);
    u64_t total_waste_time = total_time - total_final_time;

    printf(
        " The "BOLD_TXT("total")" time is " TRANSPARENT_TXT("=>") INF_TXT(" %ld:%ld:%ld\n"), 
        total_time / 3600,
        (total_time % 3600) / 60,
        (total_time % 60)
    );

    printf(
        " The "BOLD_TXT("waste")" time is " TRANSPARENT_TXT("=>") DNG_TXT(" %ld:%ld:%ld\n"), 
        total_waste_time / 3600,
        (total_waste_time % 3600) / 60,
        (total_waste_time % 60)
    );
    
    printf(
        " The "BOLD_TXT("final")" time is " TRANSPARENT_TXT("=>") OK_TXT(" %ld:%ld:%ld\n"), 
        total_final_time / 3600,
        (total_final_time % 3600) / 60,
        (total_final_time % 60)
    );
}


handle_t time_handle(guarded_t* arg) {

    
    thread_arg_t* cmd_arg   = arg->data.ptr;

    data_master_t   master  = cmd_arg->master;
    time_command_t* command = &cmd_arg->command;
    time_mode_t*    mode    = &cmd_arg->mode;
    str_t           version = cmd_arg->version;

    // starting temperory timer for calculating waste time
    clocker_timer_t tmp_timer = timer_new();

    // starting main timer for calculating whole time
    clocker_timer_t main_timer = data_master_get_timer(&master);

    // start main timer
    timer_start(&main_timer);

    // creating new mouse-keyboard event listener
    listener_t listener = listener_new();
    if (listener.inner == 0) {
        debug_err("Creating new listener failed!");
        _exit(-1);
    }

    bool_t is_paused   = B_False;
    u64_t  saver_count = 0;
    do {
        // calculating time if is in paused mode
        if (is_paused) {
            timer_reduce(&main_timer, 1);
        }

        // calculating time if is in normal mode
        else {
            // temperory timer start 
            timer_start(&tmp_timer);
            
            // listen to keyboard-mouse events
            listener_listen(&listener);
            
            // temperory timer pause
            timer_pause(&tmp_timer);

            // calculating waste time
            u64_t waste_time = timer_time_spend(&tmp_timer);
            if (waste_time > 120 && 
                (*mode) != TM_Busy &&
                !is_paused
            ) {
                // if waste time was more than 2 min, reducing main time
                timer_reduce(&main_timer, waste_time);
            }

            // reset temperory timer
            timer_reset(&tmp_timer);
        }

        // get report
        if (*command == TC_Report) {
            // first pause main timer
            timer_pause(&main_timer);
            
            // print time
            time_print(&main_timer);

            // reset command
            *command = TC_None;

            // resume main timer
            timer_resume(&main_timer);
        }

        // pause time start
        if (*command == TC_Pause) {

            // reset command
            *command = TC_None;
            is_paused = B_True;
        }

        // pause time end
        if (*command == TC_Resume) {

            // reset command
            *command = TC_None;
            is_paused = B_False;
        }

        if ((saver_count % 5 == 0 && 
            *command != TC_Save &&
            data_master_allow_saving(&master))
        ) {
            // first pause main timer
            timer_pause(&main_timer);
            
            // save time
            data_master_save_data(&master, &main_timer, B_False);

            // reset command
            *command = TC_None;

            // resume main timer
            timer_resume(&main_timer);
        }

        // wait for 1 sec
        sleep(1);
        saver_count++;
        
    // while listener is fired or program is not terminated, continue
    } while (*command != TC_End);

    // outside of the loop, the main time is over!
    timer_stop(&main_timer);
    time_print(&main_timer);

    guarded_unlock(arg);
    data_master_off(master, &main_timer);

    timer_destroy(tmp_timer);
    timer_destroy(main_timer);

    return INVALID_HNDL;
}
