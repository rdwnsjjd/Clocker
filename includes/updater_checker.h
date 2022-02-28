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

#ifndef _INCLUDES_UPDATER_CHECKER_H_
#define _INCLUDES_UPDATER_CHECKER_H_

#include "common/defs/inc.h"
#include "framework/prims/inc.h"

typedef enum {
    US_Error,
    US_NoUpdate,
    US_Updatable
}
update_status_t;

typedef u64_t updater_t;


updater_t update_checker_new();

update_status_t update_checker_check(updater_t updater);

str_t update_checker_get_version(updater_t updater);

str_t update_checker_get_new_tag(updater_t updater);

#endif // _INCLUDES_UPDATER_CHECKER_H_
