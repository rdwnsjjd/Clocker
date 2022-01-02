/**
 * Copyright (C) 2022 Redwan
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
#include <sys/time.h>


#include "data_master.h"
#include "../../common/defs.h"

typedef struct passwd  Passwd;
typedef struct stat    Stat;
typedef struct dirent  Dirnet;
typedef struct timeval TimeEval;

typedef enum {
    DFS_Nothing,
    DFS_Saved,
    DFS_NotSaved
}
DataFileState;

typedef struct {
    Str     home_dir;
    Char    main_dir[4096];
    Char    data_file[4096];
    Char    lock_file[4096];
    Stat    stat_var;
}
Paths;

typedef struct {
    FILE*      data_file_handle;
    FILE*      lock_file_handle;
    Paths      paths;
    Timer      timer;
    Bool       saving;
    Bool       is_locked;
}
_DataMaster;


Void paths_get(_DataMaster* master) {
    master->paths.home_dir = getpwuid(getuid())->pw_dir;

    sprintf(master->paths.main_dir,  "%s/%s",    master->paths.home_dir, ".config/clocker");
    sprintf(master->paths.data_file, "%s/%s", master->paths.main_dir, "data");
    sprintf(master->paths.lock_file, "%s/%s", master->paths.main_dir, "lock");
}


Bool data_master_dir_init(_DataMaster* master) {

    soft_assert_ret_id(master->paths.main_dir,  "Invalid argument (main_dir is null)!");
    soft_assert_ret_id(master->paths.data_file, "Invalid argument (main_dir is null)!");
    soft_assert_ret_id(master->paths.home_dir,  "Invalid argument (main_dir is null)!");
    soft_assert_ret_id(master->paths.lock_file, "Invalid argument (main_dir is null)!");

    if (!(stat(master->paths.main_dir, &master->paths.stat_var) == 0 &&
        S_ISDIR(master->paths.stat_var.st_mode))
    ) {
        soft_assert_ret_id(
            mkdir(master->paths.main_dir, 0700) == 0,
            "Creating main app directory failed: (%s)!",
            strerror(errno)
        );
    }

    return True;
}


Bool data_master_file_init(_DataMaster* master) {

    master->data_file_handle = fopen(master->paths.data_file, "r");
    if (master->data_file_handle == INVALID_HNDL) {

        master->data_file_handle = fopen(master->paths.data_file, "w");
        soft_assert_ret_id(
            master->data_file_handle != INVALID_HNDL,
            "Creating main app data file failed: (%s)!",
            strerror(errno)
        );
    }

    soft_assert_ret_id(
        fclose(master->data_file_handle) == 0,
        "Failed to close data file: (%s)!",
        strerror(errno)
    );

    return True;
}


Bool data_master_lock_init(_DataMaster* master) {

    master->lock_file_handle = fopen(master->paths.lock_file, "r");
    if (master->lock_file_handle == INVALID_HNDL) {

        master->lock_file_handle = fopen(master->paths.lock_file, "w");
        soft_assert_ret_id(
            master->lock_file_handle != INVALID_HNDL,
            "Creating main app lock file failed: (%s)!",
            strerror(errno)
        );
    }

    soft_assert_ret_id(
        fclose(master->lock_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return True;
}


Bool data_master_lock(_DataMaster* master) {

    Bool first_time = True;

    loop {
        master->lock_file_handle = fopen(master->paths.lock_file, "r");
        soft_assert_ret_id(
            master->lock_file_handle != INVALID_HNDL, 
            "Opening main app lock file failed: (%s)!", 
            strerror(errno)
        );
        
        Int64 locked = fgetc(master->lock_file_handle);
        if (locked == True) {

            if (first_time) {
                printf(DNG_TXT("Blocked! waiting...")"\n");
                printf(TRANSPARENT_TXT("NOTE: Another Clocker app is running on your system!\n"\
                    TRANSPARENT_TXT("If you want to make this one running, run `clocker --no-save`\n")\
                ));
                first_time = False;
            }

            sleep(5);
            
            soft_assert_ret_id(
                fclose(master->lock_file_handle) == 0,
                "Failed to close lock file: (%s)!",
                strerror(errno)
            );
        }

        else {
            fclose(master->lock_file_handle);

            master->lock_file_handle = fopen(master->paths.lock_file, "w");
            soft_assert_ret_id(
                master->lock_file_handle != INVALID_HNDL, 
                "Failed to open lock file: (%s)!",
                strerror(errno)
            );

            fputc(True, master->lock_file_handle);
            break;
        }
    }

    soft_assert_ret_id(
        fclose(master->lock_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return True;
}


Bool data_master_unlock(_DataMaster* master) {

    master->lock_file_handle = fopen(master->paths.lock_file, "w");
    soft_assert_ret_id(
        master->lock_file_handle != INVALID_HNDL, 
        "Failed to open main app lock file: (%s)!",
        strerror(errno)
    );

    fputc(False, master->lock_file_handle);

    soft_assert_ret_id(
        fclose(master->lock_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return True;
}


DataFileState data_master_check_data(_DataMaster* master) {

    master->data_file_handle = fopen(master->paths.data_file, "r");
    soft_assert_ret_id(
        master->data_file_handle != INVALID_HNDL, 
        "Opening main app data file failed: (%s)!", 
        strerror(errno)
    );

    DataFileState ret = DFS_Nothing;

    Bool state = (Bool) (fgetc(master->data_file_handle) - '0');
    switch (state) {
        case True:
            ret = DFS_Saved;
            break;
        case False:
            ret = DFS_NotSaved;
            break;
        default:
            break;
    };

    soft_assert_ret_id(
        fclose(master->data_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return ret;
}


Bool data_master_read_data(_DataMaster* master) {

    master->data_file_handle = fopen(master->paths.data_file, "r");
    soft_assert_ret_id(
        master->data_file_handle != INVALID_HNDL, 
        "Opening main app data file failed: (%s)!", 
        strerror(errno)
    );

    Char buff[32] = {'\000'};
    fgets(buff, 32, master->data_file_handle);

    Str  cur = buff;

    Char total[8] = {0};
    Char final[8] = {0};
    Char now[16]  = {0};
    Str tmp       = INVALID_HNDL;
    Idx last      = 0;

    for (Idx idx = 0;; cur++, idx++) {

        if (*cur == '>') {
            tmp  = cur + 1;
            last = idx + 1;
        }

        else if (*cur == '/') {
            memcpy(now, tmp, idx - last);
            tmp  = cur + 1;
            last = idx + 1;
        }

        else if (*cur == '-') {
            memcpy(total, tmp, idx - last);
            tmp  = cur + 1;
            last = idx + 1;
        }

        else if (*cur == '\000') {
            memcpy(final, tmp, idx - last);
            tmp  = cur + 1;
            last = idx + 1;
            break;
        }
    }
    
    master->timer = timer_init(atol(total), atol(final));
    soft_assert_ret_id(master->timer != 0, "Initializing new timer failed!");

    soft_assert_ret_id(
        fclose(master->data_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return True;
}


Bool data_master_save_data(
    DataMaster master, 
    Timer      timer, 
    Bool       final
) {

    TimeEval     time    = {0};
    _DataMaster* _master = (_DataMaster*) master;

    _master->data_file_handle = fopen(_master->paths.data_file, "w");
    soft_assert_ret_id(
        _master->data_file_handle != INVALID_HNDL, 
        "Opening main app data file failed: (%s)!", 
        strerror(errno)
    );

    gettimeofday(&time, INVALID_HNDL);
    UInt64 a = timer_get_time(timer);
    UInt64 b = timer_time_spend(timer);
    fprintf(
        _master->data_file_handle, 
        "%d>%ld/%ld-%ld", 
        final, 
        time.tv_sec,
        a, 
        b
    );
    
    soft_assert_ret_id(
        fclose(_master->data_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return True;
}


Bool data_master_clear_data(_DataMaster* master) {
    master->timer = timer_new();
    soft_assert_ret_id(master->timer != 0, "Creating new timer failed!");

    return True;
}


DataMaster data_master_on(Bool no_save) {

    _DataMaster* new = (_DataMaster*) malloc(sizeof(_DataMaster));
    soft_assert_ret_id(new != INVALID_HNDL, "Allocating new updater failed!");

    paths_get(new);
    new->saving = !no_save;

    if (new->saving) {
        soft_assert_ret_id(
            data_master_lock_init(new),
            "Initializing app lock file failed!"
        );

        soft_assert_ret_id(
            data_master_lock(new),
            "Initializing app lock file failed!"
        );
    }

    soft_assert_ret_id(
        data_master_dir_init(new),
        "Initializing app main directory failed!"
    );

    soft_assert_ret_id(
        data_master_file_init(new),
        "Initializing app data file failed!"
    );

    if (data_master_check_data(new) != DFS_Nothing && new->saving) {
        printf(INF_TXT("There are some data from last time Clocker was run.\n"\
              "Do you want to resotre and continue that?[Y/n]")
        );

        Char result = fgetc(stdin);
        if (result == '\n' || result == 'Y' || result == 'y') {
            soft_assert_ret_id(
                data_master_read_data(new),
                "Reading data failed!"
            );

            return (DataMaster) new;
        }
    }

    soft_assert_ret_id(
        data_master_clear_data(new),
        "Clearing data failed!"
    );
        
    return (DataMaster) new;
}


Void data_master_off(DataMaster master, Timer timer) {

    _DataMaster* _master = (_DataMaster*) master;

    if (_master->saving) {

        soft_assert_ret_id(
            data_master_save_data(master, timer, True),
            "Initializing app data file failed!"
        );

        soft_assert_ret_id(
            data_master_unlock(_master),
            "Initializing app lock file failed!"
        );
    }

    timer_destroy(_master->timer);
    free(_master);
}


Timer data_master_get_timer(DataMaster master) {

    _DataMaster* _master = (_DataMaster*) master;

    return _master->timer;
}


Timer data_master_allow_saving(DataMaster master) {

    _DataMaster* _master = (_DataMaster*) master;

    return _master->saving;
}