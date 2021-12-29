#include "../../headers/mutexed.h"

#include <stdlib.h>

Mutexed* mutexed_new(GenType inner) {

    Mutexed* new = (Mutexed*) malloc(sizeof(Mutexed));
    soft_assert_ret_void(new != INVALID_HNDL, "Allocating new mutexed failed!");

    new->mutex = (Mutex) {0};
    new->inner = inner;

    pthread_mutex_init(&new->mutex, INVALID_HNDL);

    return new;
}

Void mutexed_change(Mutexed* mutexed, GenType value) {
    pthread_mutex_lock(&mutexed->mutex);
    mutexed->inner = value;
    pthread_mutex_unlock(&mutexed->mutex);
}

Void mutexed_destroy(Mutexed* mutexed) {
    pthread_mutex_destroy(&mutexed->mutex);
    free(mutexed);
}