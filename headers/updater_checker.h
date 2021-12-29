#ifndef HEADERS_UPDATECHRCKER_H
#define HEADERS_UPDATECHRCKER_H

#include "../includes/common/inc.h"

typedef enum {
    US_Error,
    US_NoUpdate,
    US_Updatable
}
UpdateStatus;

typedef UInt64 Updater;


Updater update_checker_new();

UpdateStatus update_checker_check(Updater updater);

Str update_checker_get_version(Updater updater);

Str update_checker_get_new_tag(Updater updater);

#endif // HEADERS_UPDATECHRCKER_H