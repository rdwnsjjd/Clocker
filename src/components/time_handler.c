#include <unistd.h>

#include "../../headers/time_handler.h"
#include "../../headers/timer.h"
#include "../../headers/listener.h"
#include "../../headers/mutexed.h"

Hndl time_handle(Void* arg) {

    Mutexed* state = (Mutexed*) arg;

    // starting temperory timer for calculating waste time
    Timer tmp_timer = timer_new();

    // starting main timer for calculating whole time
    Timer main_timer = timer_new();

    // start main timer
    timer_start(main_timer);

    // creating new mouse-keyboard event listener
    Listener listener = listener_new();

    do {
        // temperory timer start 
        timer_start(tmp_timer);
        

        // listen to keyboard-mouse events
        listener_listen(listener);
        
        // temperory timer pause
        timer_pause(tmp_timer);

        // calculating waste time
        UInt64 waste_time = timer_time_spend(tmp_timer);
        if (waste_time > 120 && state->inner.i32 != 2) {
            // if waste time was more than 2 min, reducing main time
            timer_reduce(main_timer, waste_time);
        }

        timer_reset(tmp_timer);
        sleep(1);
        
    // while listener is fired or program is not terminated, continue
    } while (state->inner.i32 != 1);

    // outside of the loop, the main time is over!
    timer_stop(main_timer);

    UInt64 total_time       = time_get_time(main_timer);
    UInt64 total_final_time = timer_time_spend(main_timer);
    UInt64 total_waste_time = total_time - total_final_time;

    printf(
        "The total time is => %ld:%ld:%ld\n", 
        total_time / 3600,
        (total_time % 3600) / 60,
        (total_time % 60)
    );

    printf(
        "The total waste time is => %ld:%ld:%ld\n", 
        total_waste_time / 3600,
        (total_waste_time % 3600) / 60,
        (total_waste_time % 60)
    );
    
    printf(
        "The final time is => %ld:%ld:%ld\n", 
        total_final_time / 3600,
        (total_final_time % 3600) / 60,
        (total_final_time % 60)
    );

}
