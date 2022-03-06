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

#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct passwd passwd_t;
typedef struct stat   stat_t;
typedef struct dirent dirnet_t;

#include "common/defs/program_defs.h"
#include "includes/updater_checker.h"

typedef struct {
    byte_t version[32];
    byte_t new_version[32];
}
updater_inner_t;


updater_t update_checker_new() {
    boxed_t boxed = boxed_new(sizeof(updater_inner_t));
    soft_assert_ret(boxed_unbox(&boxed) != INVALID_HNDL, (updater_t) {.inner = 0}, "Allocating new updater failed!");

    updater_inner_t* new = (updater_inner_t*) boxed_unbox(&boxed);

    stat_t    stat_var          = {0};
    passwd_t* home_dir          = getpwuid(getuid());
    char_t    config_file[4096] = {0};

    sprintf(config_file, "%s/%s", home_dir->pw_dir, ".config/clocker/clocker.conf");

    size_t config_file_size = 0;
    FILE* config_file_ptr = fopen(config_file, "r");

    if (config_file_ptr == INVALID_HNDL) {

        config_file_ptr = fopen(config_file, "w");
        soft_assert_ret(
            config_file_ptr != INVALID_HNDL,
            (updater_t) {.inner = 0},
            "Creating main app config file failed! (%s)",
            strerror(errno)
        );

        fputs(INIT_VERSION, config_file_ptr);
        config_file_size = strlen(INIT_VERSION);

        memcpy(new->version, INIT_VERSION, config_file_size);
    }

    else {
        // getting data file size
        fseek(config_file_ptr, 0L, SEEK_END);
        config_file_size = ftell(config_file_ptr);
        fseek(config_file_ptr, 0L, SEEK_SET);

        fscanf(config_file_ptr, "%s", new->version);
    }

    soft_assert_ret(
        fclose(config_file_ptr) == 0,
        (updater_t) {.inner = 0},
        "Closing main app config failed! (%s)",
        strerror(errno)
    );

    return (updater_t) {.inner = boxed};
}


update_status_t update_checker_check(updater_t* updater) {

    updater_inner_t* _updater = (updater_inner_t*) boxed_unbox(&updater->inner);

    soft_assert_ret_id(
        system("wget https://api.github.com/repos/rdwnsjjd/clocker/tags -P /root/.config/clocker/.tags --quiet") == 0,
        "Cannot get available version of clocker!"
    );

    FILE* tags_file_ptr = fopen("/root/.config/clocker/.tags/tags", "r");
    soft_assert_ret_id(tags_file_ptr != INVALID_HNDL, "Tag file is missed!");

    // getting tags file size
    fseek(tags_file_ptr, 0L, SEEK_END);
    size_t tags_file_size = ftell(tags_file_ptr);
    fseek(tags_file_ptr, 0L, SEEK_SET);

    boxed_t boxed = boxed_new(sizeof(byte_t) * tags_file_size);
    soft_assert_ret_id(boxed_unbox(&boxed) != INVALID_HNDL, "Creating new boxed pointer failed!");
    str_t available_version = (str_t) boxed_unbox(&boxed);

    for (index_t idx = 0; idx < tags_file_size; idx++) {
        available_version[idx] = fgetc(tags_file_ptr);
    }

    str_t   cur             = available_version;
    bool_t  target_expected = B_False;
    index_t last_index      = 0;

    for (index_t idx = 0; *cur != EOF; cur++, idx++) {

        if (*cur == ' ' || *cur == '\n') {
            continue;
        }

        if (*cur == 'n' && *(cur + 1) == 'a' && *(cur + 2) == 'm' && *(cur + 3) == 'e') {
            cur += 9;
            target_expected = B_True;
            idx += 9;
            last_index = idx;
        }

        if (*cur == '\"' && target_expected) {
            
            size_t len = idx - last_index;

            boxed_t string_boxed = boxed_zeroed_new(1, len);
            soft_assert_ret_id(boxed_unbox(&string_boxed) != INVALID_HNDL, "Creating new boxed pointer for string failed!");
            str_t string = (str_t) boxed_unbox(&string_boxed);

            memcpy(string, available_version + last_index, len);
            if (strncmp(_updater->version, string, 32) == 0) {

                soft_assert_ret_id(
                    fclose(tags_file_ptr) == 0,
                    "Closing tags file failed! (%s)",
                    strerror(errno)
                );

                soft_assert_ret_id(
                    remove("/root/.config/clocker/.tags/tags") == 0,
                    "Deleting tags file failed (%s)",
                    strerror(errno)
                );

                boxed_destroy(boxed);
                boxed_destroy(string_boxed);
                return US_NoUpdate;
            }

            else {
                memcpy(_updater->new_version, string, len);

                soft_assert_ret_id(
                    fclose(tags_file_ptr) == 0,
                    "Closing tags file failed! (%s)",
                    strerror(errno)
                );

                soft_assert_ret_id(
                    remove("/root/.config/clocker/.tags/tags") == 0,
                    "Deleting tags file failed (%s)",
                    strerror(errno)
                );

                boxed_destroy(boxed);
                boxed_destroy(string_boxed);
                return US_Updatable;
            }

            boxed_destroy(string_boxed);
        }
    }
    boxed_destroy(boxed);
}


str_t update_checker_get_version(updater_t* updater) {
    updater_inner_t* _updater = (updater_inner_t*) boxed_unbox(&updater->inner);
    return _updater->version;
}


// str_t update_checker_get_version(updater_t* updater) {
//     updater_inner_t* _updater = (updater_inner_t*) boxed_unbox(&updater->inner);
//     return _updater->version;
// }


str_t update_checker_get_new_tag(updater_t* updater) {
    updater_inner_t* _updater = (updater_inner_t*) boxed_unbox(&updater->inner);
    return _updater->new_version;
}


void_t update_checker_destroy(updater_t updater) {
    boxed_destroy(updater.inner);
}