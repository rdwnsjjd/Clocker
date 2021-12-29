#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct passwd Passwd;
typedef struct stat   Stat;
typedef struct dirent Dirnet;

#include "../../headers/updater_checker.h"

typedef struct {
    Str version;
    Str new_version;
}
_Updater;


Updater update_checker_new() {
    _Updater* new = (_Updater*) malloc(sizeof(_Updater));
    soft_assert_ret_id(new != INVALID_HNDL, "Allocating new updater failed!");

    Passwd* home_dir       = getpwuid(getuid());
    Char    data_dir[128]  = {0};
    Char    data_file[128] = {0};
    Stat    stat_var       = {0};

    sprintf(data_dir, "%s/%s", home_dir->pw_dir, ".clocker");
    sprintf(data_file, "%s/%s", home_dir->pw_dir, ".clocker/clocker.conf");

    if (
        !(stat(data_dir, &stat_var) == 0 &&
        S_ISDIR(stat_var.st_mode))
    ) {

        soft_assert_ret_id(
            mkdir(data_dir, 0700) == 0,
            "Creating main app directory failed! (%s)",
            strerror(errno)
        );

        FILE* data_file_ptr = fopen(data_file, "w");
        soft_assert_ret_id(
            data_file_ptr != INVALID_HNDL,
            "Creating main app data file failed! (%s)",
            strerror(errno)
        );

        fputs("0.0-beta.0", data_file_ptr);

        soft_assert_ret_id(
            fclose(data_file_ptr) == 0,
            "Closing main app data failed! (%s)",
            strerror(errno)
        );
    }
    
    FILE* data_file_ptr = fopen(data_file, "r");
    soft_assert_ret_id(data_file_ptr != INVALID_HNDL, "App data file is missed!");

    // getting data file size
    fseek(data_file_ptr, 0L, SEEK_END);
    Size data_file_size = ftell(data_file_ptr);
    fseek(data_file_ptr, 0L, SEEK_SET);

    new->version = (Str) malloc(sizeof(Char) * data_file_size);
    soft_assert_ret_id(new->version != INVALID_HNDL, "Allocating new string failed!");
    // fgets(d, 10, data_file_ptr);
    fscanf(data_file_ptr, "%s", new->version);

    soft_assert_ret_id(
        fclose(data_file_ptr) == 0,
        "Closing main app data failed! (%s)",
        strerror(errno)
    );

    return (Updater) new;
}


UpdateStatus update_checker_check(Updater updater) {

    _Updater* _updater = (_Updater*) updater;

    soft_assert_ret_id(
        system("wget https://api.github.com/repos/rdwnsjjd/clocker/tags -P /root/.clocker/.tags --quiet") == 0,
        "Cannot get available version of clocker!"
    );

    FILE* tags_file_ptr = fopen("/root/.clocker/.tags/tags", "r");
    soft_assert_ret_id(tags_file_ptr != INVALID_HNDL, "Tag file is missed!");

    // getting tags file size
    fseek(tags_file_ptr, 0L, SEEK_END);
    Size tags_file_size = ftell(tags_file_ptr);
    fseek(tags_file_ptr, 0L, SEEK_SET);

    Str available_version = (Str) malloc(sizeof(Char) * tags_file_size);
    soft_assert_ret_id(available_version != INVALID_HNDL, "Allocating new string failed!");

    for (Idx idx = 0; idx < tags_file_size; idx++) {
        *(available_version + idx) = fgetc(tags_file_ptr);
    }

    Str  cur             = available_version;
    Bool target_expected = False;
    Idx  last_index      = 0;

    for (Idx idx = 0; *cur != EOF; cur++, idx++) {

        if (*cur == ' ' || *cur == '\n') {
            continue;
        }

        if (*cur == 'n' && 
            *(cur + 1) == 'a' && 
            *(cur + 2) == 'm' && 
            *(cur + 3) == 'e'
        ) {
            cur += 9;
            target_expected = True;

            idx += 9;
            last_index = idx;
            
        }

        if (*cur == '\"' && target_expected) {
            
            Size len = idx - last_index;

            Str string = (Str) calloc(1, len);
            soft_assert_ret_id(string != INVALID_HNDL, "Allocating new string failed!");

            memcpy(string, available_version + last_index, len);
            if (strcmp(_updater->version, string) == 0) {

                soft_assert_ret_id(
                    fclose(tags_file_ptr) == 0,
                    "Closing tags file failed! (%s)",
                    strerror(errno)
                );

                soft_assert_ret_id(
                    remove("/root/.clocker/.tags/tags") == 0,
                    "Deleting tags file failed (%s)",
                    strerror(errno)
                );

                free(available_version);
                return US_NoUpdate;
            }

            else {
                _updater->new_version = string;

                soft_assert_ret_id(
                    fclose(tags_file_ptr) == 0,
                    "Closing tags file failed! (%s)",
                    strerror(errno)
                );

                soft_assert_ret_id(
                    remove("/root/.clocker/.tags/tags") == 0,
                    "Deleting tags file failed (%s)",
                    strerror(errno)
                );

                free(available_version);

                return US_Updatable;
            }
        }
    }
    
}


Str update_checker_get_version(Updater updater) {
    _Updater* _updater = (_Updater*) updater;
    return _updater->version;
}


Str update_checker_get_new_tag(Updater updater) {
    _Updater* _updater = (_Updater*) updater;
    return _updater->new_version;
}