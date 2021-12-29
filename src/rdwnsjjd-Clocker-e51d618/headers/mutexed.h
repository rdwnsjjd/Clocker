#ifndef HEDARS_MUTEX_H
#define HEDARS_MUTEX_H

#include "../includes/common/inc.h"

#include <pthread.h>

typedef pthread_mutex_t Mutex;

typedef struct {
    Mutex    mutex;
    GenType  inner;
}
Mutexed;

Mutexed* mutexed_new(GenType inner);

Void mutexed_change(Mutexed* mutexed, GenType value);

Void mutexed_destroy(Mutexed* mutexed);


#endif // HEDARS_MUTEX_H