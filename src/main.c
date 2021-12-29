#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "../includes/common/inc.h"
#include "../headers/time_handler.h"
#include "../headers/mutexed.h"
#include "../headers/updater.h"

typedef pthread_t       Thread;

Int32 main() {

    Updater updater = updater_new();
    soft_assert_wrn(
        updater != 0,
        "Creating new update object failed!"
    );

    UpdateStatus update_res = updater_check(updater);
    soft_assert_wrn(
        update_res != US_Error,
        "Checking for new version failed!"
    );

    if (update_res == US_Updatable) {
        printf(
            "Version %s is available!\nDo you want to install it? [Y/n]", 
            updater_get_new_tag(updater)
        );

        Char result = fgetc(stdin);
        if (result == '\n' || result == 'Y' || result == 'y') {
            updater_do_update(updater);
        }
        else {
            printf("Aborted!\n\n");
        }
    }

    printf("Hello!\n Wellcomfgsdge to Clocker!\n");

    Mutexed* state = mutexed_new(gen_type(0));
    soft_assert_ret_int(state != INVALID_HNDL, "Failed to create new mutexed!");

    // creating time handling thread
    Thread termination_thread = 0;
    pthread_create(
        &termination_thread, 
        INVALID_HNDL, 
        time_handle, 
        (Hndl) state
    );

    loop {
        printf("> ");
        Char input[1024] = {0};
        scanf("%s", input);

        if (input[0] == 'e' && input[1] == 'n' && input[2] == 'd') {
            mutexed_change(state, gen_type(1));
            break;
        }

        else if (strcmp(input, "non-stop") == 0) {
            mutexed_change(state, gen_type(2));
        }

        else if (strcmp(input, "normal") == 0) {
            mutexed_change(state, gen_type(0));
        }

        else if (strcmp(input, "get-time") == 0) {
            mutexed_change(state, gen_type(3));
        }
        
        else {
            printf("Invalid command!\n");
        }
    }

    // printf("Terminated!");
    pthread_join(termination_thread, INVALID_HNDL);
    
}