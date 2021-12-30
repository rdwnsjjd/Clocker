#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "../includes/common/inc.h"
#include "../headers/time_handler.h"
#include "../headers/mutexed.h"
#include "../headers/updater_checker.h"

typedef pthread_t       Thread;

Int32 main(
    Int32 argc,
    Str   argv[]
) {

    if (argv[1] && strcmp(argv[1], "--update") == 0) {

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

            printf(
                "Version %s is available!\nyou have version %s!\nDo you want to install it? [Y/n]", 
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

    printf("Hello!\n Welcome to Clocker!\n");

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

        else if (strcmp(input, "busy") == 0) {
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
