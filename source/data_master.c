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


#include "includes/data_master.h"
#include "common/defs/inc.h"

typedef struct passwd  passwd_t;
typedef struct stat    stat_t;
typedef struct dirent  dirnet_t;
typedef struct timeval time_eval_t;

typedef enum {
    DFS_Nothing,
    DFS_Saved,
    DFS_NotSaved
}
data_file_status_t;

typedef struct {
    data_file_status_t state;
    bool_t             is_locked; 
}
data_file_lock_t;

typedef struct {
    u64_t      total;
    u64_t      final;
    u64_t      now;
}
data_file_data_t;

typedef struct {
    UNSAFE str_t  home_dir;
    UNSAFE char_t main_dir[1024];
    UNSAFE char_t data_file[2048];
    UNSAFE char_t lock_file[4096];
    stat_t        stat_var;
}
paths_t;

typedef struct {
    UNSAFE FILE*   data_file_handle;
    UNSAFE FILE*   lock_file_handle;
    paths_t         paths;
    clocker_timer_t timer;
    bool_t          saving;
    bool_t          is_locked;
}
data_master_inner_t;


void_t paths_get(data_master_inner_t MUT* master) {
    master->paths.home_dir = getpwuid(getuid())->pw_dir;

    sprintf(master->paths.main_dir,  "%s/%s", master->paths.home_dir, ".config/clocker");
    sprintf(master->paths.data_file, "%s/%s", master->paths.main_dir, "data");
    sprintf(master->paths.lock_file, "%s/%s", master->paths.main_dir, "lock");
}


bool_t data_master_dir_init(data_master_inner_t* master) {

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

    return B_True;
}


bool_t data_master_file_init(data_master_inner_t* master) {

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

    return B_True;
}


bool_t data_master_lock_init(data_master_inner_t* master) {

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

    return B_True;
}


void_t data_master_get_lock(
    data_master_inner_t*  master, 
    data_file_lock_t* lock
) {

    master->lock_file_handle = fopen(master->paths.lock_file, "r");
    soft_assert_ret_id(
        master->lock_file_handle != INVALID_HNDL, 
        "Opening main app lock file failed: (%s)!", 
        strerror(errno)
    );

    fgets((bytes_t)lock, sizeof(data_file_lock_t), master->lock_file_handle);

    soft_assert_ret_id(
        fclose(master->lock_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return;
}


bool_t data_master_lock(data_master_inner_t* master) {

    bool_t first_time   = B_True;
    data_file_lock_t lock = {0};
    data_master_get_lock(master, &lock);

    loop {

        if (lock.is_locked) {

            if (first_time) {
                printf(DNG_TXT("Blocked! waiting...")"\n");
                printf(TRANSPARENT_TXT("NOTE: Another Clocker app is running on your system!\n"\
                    TRANSPARENT_TXT("If you want to make this one running, run `clocker --no-save`\n")\
                ));
                first_time = B_False;
            }

            data_master_get_lock(master, &lock);
            sleep(5);
        }

        else {

            master->lock_file_handle = fopen(master->paths.lock_file, "w");
            soft_assert_ret_id(
                master->lock_file_handle != INVALID_HNDL, 
                "Failed to open lock file: (%s)!",
                strerror(errno)
            );

            lock.state     = (lock.state == DFS_Nothing) ? DFS_NotSaved : lock.state;
            lock.is_locked = B_True;

            for (index_t idx = 0; idx < sizeof(data_file_lock_t); idx++) {
                fputc(((bytes_t)&lock)[idx], master->lock_file_handle);
            }

            break;
        }
    }

    soft_assert_ret_id(
        fclose(master->lock_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return B_True;
}


bool_t data_master_unlock(data_master_inner_t* master) {

    master->lock_file_handle = fopen(master->paths.lock_file, "w");
    soft_assert_ret_id(
        master->lock_file_handle != INVALID_HNDL, 
        "Failed to open main app lock file: (%s)!",
        strerror(errno)
    );

    data_file_lock_t lock = {
        .state     = DFS_Saved,
        .is_locked = B_False
    };

    for (index_t idx = 0; idx < sizeof(data_file_lock_t); idx++) {
        fputc(((bytes_t)&lock)[idx], master->lock_file_handle);
    }

    soft_assert_ret_id(
        fclose(master->lock_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return B_True;
}


bool_t data_master_read_data(data_master_inner_t* master) {

    master->data_file_handle = fopen(master->paths.data_file, "r");
    soft_assert_ret_id(
        master->data_file_handle != INVALID_HNDL, 
        "Opening main app data file failed: (%s)!", 
        strerror(errno)
    );

    data_file_data_t data = {0};
    fgets((bytes_t)& data, sizeof(data_file_data_t), master->data_file_handle);
    
    timer_init(&master->timer, data.total, data.final);
    soft_assert_ret_id(master->timer.inner != 0, "Initializing new timer failed!");

    soft_assert_ret_id(
        fclose(master->data_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return B_True;
}


PUB
bool_t data_master_save_data(
    data_master_t*   master, 
    clocker_timer_t* timer, 
    bool_t           final
) {

    time_eval_t     time    = {0};
    data_master_inner_t* _master = (data_master_inner_t*) master->inner;

    _master->data_file_handle = fopen(_master->paths.data_file, "w");
    soft_assert_ret_id(
        _master->data_file_handle != INVALID_HNDL, 
        "Opening main app data file failed: (%s)!", 
        strerror(errno)
    );

    gettimeofday(&time, INVALID_HNDL);

    data_file_data_t data = {
        .now   = time.tv_sec,
        .total = timer_get_time(timer),
        .final = timer_time_spend(timer)
    };

    for (index_t idx = 0; idx < sizeof(data_file_data_t); idx++) {
        fputc(((bytes_t)&data)[idx], _master->data_file_handle);
    }
    
    
    soft_assert_ret_id(
        fclose(_master->data_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return B_True;
}


bool_t data_master_clear_data(data_master_inner_t* master) {
    master->timer = timer_new();
    soft_assert_ret_id(master->timer.inner != 0, "Creating new timer failed!");

    return B_True;
}


PUB 
data_master_t data_master_on(bool_t no_save) {

    data_master_inner_t* new = (data_master_inner_t*) malloc(sizeof(data_master_inner_t));
    soft_assert_ret(new != INVALID_HNDL, (data_master_t) {.inner = 0}, "Allocating new updater failed!");

    paths_get(new);
    new->saving = !no_save;

    if (new->saving) {
        soft_assert_ret(
            data_master_lock_init(new),
            (data_master_t) {.inner = 0},
            "Initializing app lock file failed!"
        );

        soft_assert_ret(
            data_master_lock(new),
            (data_master_t) {.inner = 0},
            "Initializing app lock file failed!"
        );
    }

    soft_assert_ret(
        data_master_dir_init(new),
        (data_master_t) {.inner = 0},
        "Initializing app main directory failed!"
    );

    soft_assert_ret(
        data_master_file_init(new),
        (data_master_t) {.inner = 0},
        "Initializing app data file failed!"
    );

    data_file_lock_t lock = {0};
    data_master_get_lock(new, &lock);
    
    if (lock.state != DFS_Nothing && new->saving) {
        printf(INF_TXT("There are some data from last time Clocker was run.\n"\
              "Do you want to resotre and continue that?[Y/n]")
        );

        char_t result = fgetc(stdin);
        if (result == '\n' || result == 'Y' || result == 'y') {
            soft_assert_ret(
                data_master_read_data(new),
                (data_master_t) {.inner = 0},
                "Reading data failed!"
            );

            return (data_master_t) (data_master_t) {.inner = (u64_t) new};
        }
    }

    soft_assert_ret(
        data_master_clear_data(new),
        (data_master_t) {.inner = 0},
        "Clearing data failed!"
    );
        
    return (data_master_t) (data_master_t) {.inner = (u64_t) new};
}


PUB
void_t data_master_off(data_master_t master, clocker_timer_t* timer) {

    data_master_inner_t* _master = (data_master_inner_t*) master.inner;

    if (_master->saving) {

        soft_assert_ret_void(
            data_master_save_data(&master, timer, B_True),
            "Initializing app data file failed!"
        );

        soft_assert_ret_void(
            data_master_unlock(_master),
            "Initializing app lock file failed!"
        );
    }

    timer_destroy(_master->timer);
    free(_master);
}


PUB
clocker_timer_t data_master_get_timer(data_master_t* master) {
    data_master_inner_t* _master = (data_master_inner_t*) master->inner;
    return _master->timer;
}


PUB
bool_t data_master_allow_saving(data_master_t* master) {
    data_master_inner_t* _master = (data_master_inner_t*) master->inner;
    return _master->saving;
}