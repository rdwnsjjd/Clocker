#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "../includes/common/inc.h"
#include "../headers/time_handler.h"
#include "../headers/mutexed.h"

typedef pthread_t       Thread;

Int32 main(
    Int32 argc,
    Str   argv[]
) {

    if (!argv[1]) {
        execvp("/home/rdwn/Documents/projs/Clocker/build/updater", INVALID_HNDL);
    }
    else if ((strcmp(argv[1], "no-update") != 0)) {
        execvp("/home/rdwn/Documents/projs/Clocker/build/updater", INVALID_HNDL);
    }

    printf("Hello!\n Wellcome to Clocker!\n");

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