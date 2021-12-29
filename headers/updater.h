#ifndef HEADERS_UPDATER_H
#define HEADERS_UPDATER_H

#include "../includes/common/inc.h"

typedef enum {
    US_Error,
    US_NoUpdate,
    US_Updatable
}
UpdateStatus;

typedef UInt64 Updater;

Updater updater_new();

Str updater_get_version(Updater updater);

Str updater_get_new_tag(Updater updater);

UpdateStatus updater_check(Updater updater);

Bool updater_do_update(Updater updater);

#endif // HEADERS_UPDATER_H