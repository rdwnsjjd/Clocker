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

#ifndef HEADERS_UPDATECHRCKER_H
#define HEADERS_UPDATECHRCKER_H

#include "../includes/common/inc.h"
#include "../common/defs.h"

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