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

#include "../../headers/time_handler.h"
#include "../../headers/timer.h"
#include "../../headers/listener.h"
#include "../../headers/mutexed.h"


Void time_print(UInt64 main_timer) {

    UInt64 total_time       = time_get_time(main_timer);
    UInt64 total_final_time = timer_time_spend(main_timer);
    UInt64 total_waste_time = total_time - total_final_time;

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
        " The "BOLD_TXT("final")" time is " TRANSPARENT_TXT("=>") ATT_TXT(" %ld:%ld:%ld\n"), 
        total_final_time / 3600,
        (total_final_time % 3600) / 60,
        (total_final_time % 60)
    );
}


Hndl time_handle(Void* arg) {

    
    TreadArg* cmd_arg = (TreadArg*) arg;
    Mutexed*  command = cmd_arg->command;
    Mutexed*  mode    = cmd_arg->mode;
    Str       version = cmd_arg->version;

    // starting temperory timer for calculating waste time
    Timer tmp_timer = timer_new();

    // starting main timer for calculating whole time
    Timer main_timer = timer_new();

    // start main timer
    timer_start(main_timer);

    // creating new mouse-keyboard event listener
    Listener listener = listener_new();
    if (listener == 0) {
        debug_err("Creating new listener failed!");
        _exit(-1);
    }

    Bool is_paused = False;
    do {

        // calculating time if is in paused mode
        if (is_paused) {
            timer_reduce(main_timer, 1);
        }

        // calculating time if is in normal mode
        else {
            // temperory timer start 
            timer_start(tmp_timer);
            
            // listen to keyboard-mouse events
            listener_listen(listener);
            
            // temperory timer pause
            timer_pause(tmp_timer);

            // calculating waste time
            UInt64 waste_time = timer_time_spend(tmp_timer);
            if (waste_time > 120 && 
                mode->inner.i32 != TM_Busy &&
                !is_paused
            ) {
                // if waste time was more than 2 min, reducing main time
                timer_reduce(main_timer, waste_time);
            }

            // reset temperory timer
            timer_reset(tmp_timer);
        }

        // get report
        if (command->inner.i64 == TC_Report) {
            // first pause main timer
            timer_pause(main_timer);
            
            // print time
            time_print(main_timer);

            // reset command
            mutexed_change(command, gen_type(TC_None));

            // resume main timer
            timer_resume(main_timer);
        }

        // pause time start
        if (command->inner.i64 == TC_Pause) {

            // reset command
            mutexed_change(command, gen_type(TC_None));

            is_paused = True;
        }

        // pause time end
        if (command->inner.i64 == TC_Resume) {

            // reset command
            mutexed_change(command, gen_type(TC_None));

            is_paused = False;
        }

        // wait for 1 sec
        sleep(1);
        
    // while listener is fired or program is not terminated, continue
    } while (command->inner.i32 != TC_End);

    // outside of the loop, the main time is over!
    timer_stop(main_timer);
    time_print(main_timer);

    return INVALID_HNDL;
}
