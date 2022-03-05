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


#include "includes/data_manager.h"
#include "common/defs/inc.h"
#include "framework/system/memory/inc.h"

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
    u64_t total;
    u64_t final;
    u64_t now;
}
data_file_data_t;

// this struct contains three pointers. but as they're array and static-defined (on stack)
// we don't need to be worried about them. we consider them as usual variables
typedef struct {
    str_t  home_dir;
    char_t main_dir[1024];
    char_t data_file[2048];
    char_t lock_file[4096];
    stat_t stat_var;
}
paths_t;

// our main data manager struct
// if we use pointer in the struct we ourself are responsible to free it.
// in other word pointer in the structs considers as `UNSAFE` item. so we are not
// allowed to use it and if use it, it means we are aware of what we're doing.
// so we prefer to avoid using pointer in the structs and if we have to do it, 
// consider freeing or destructing it in our main struct destructor.
typedef struct {
    FILE*           data_file_handle;
    FILE*           lock_file_handle;
    bool_t          saving;
    bool_t          is_locked;
    paths_t         paths;
    clocker_timer_t timer;
}
data_manager_inner_t;


void_t paths_get(data_manager_inner_t MUT* manager) {
    manager->paths.home_dir = getpwuid(getuid())->pw_dir;
    sprintf(manager->paths.main_dir,  "%s/%s", manager->paths.home_dir, ".config/clocker");
    sprintf(manager->paths.data_file, "%s/%s", manager->paths.main_dir, "data");
    sprintf(manager->paths.lock_file, "%s/%s", manager->paths.main_dir, "lock");
}


bool_t data_manager_dir_init(data_manager_inner_t* manager) {
    soft_assert_ret_id(manager->paths.main_dir,  "Invalid argument (main_dir is null)!");
    soft_assert_ret_id(manager->paths.data_file, "Invalid argument (main_dir is null)!");
    soft_assert_ret_id(manager->paths.home_dir,  "Invalid argument (main_dir is null)!");
    soft_assert_ret_id(manager->paths.lock_file, "Invalid argument (main_dir is null)!");

    if (!(stat(manager->paths.main_dir, &manager->paths.stat_var) == 0 &&
        S_ISDIR(manager->paths.stat_var.st_mode))
    ) {
        soft_assert_ret_id(
            mkdir(manager->paths.main_dir, 0700) == 0,
            "Creating main app directory failed: (%s)!",
            strerror(errno)
        );
    }

    return B_True;
}


bool_t data_manager_file_init(data_manager_inner_t* manager) {

    manager->data_file_handle = fopen(manager->paths.data_file, "r");
    if (manager->data_file_handle == INVALID_HNDL) {

        manager->data_file_handle = fopen(manager->paths.data_file, "w");
        soft_assert_ret_id(
            manager->data_file_handle != INVALID_HNDL,
            "Creating main app data file failed: (%s)!",
            strerror(errno)
        );
    }

    soft_assert_ret_id(
        fclose(manager->data_file_handle) == 0,
        "Failed to close data file: (%s)!",
        strerror(errno)
    );

    return B_True;
}


bool_t data_manager_lock_init(data_manager_inner_t* manager) {

    manager->lock_file_handle = fopen(manager->paths.lock_file, "r");
    if (manager->lock_file_handle == INVALID_HNDL) {

        manager->lock_file_handle = fopen(manager->paths.lock_file, "w");
        soft_assert_ret_id(
            manager->lock_file_handle != INVALID_HNDL,
            "Creating main app lock file failed: (%s)!",
            strerror(errno)
        );
    }

    soft_assert_ret_id(
        fclose(manager->lock_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return B_True;
}


void_t data_manager_get_lock(
    data_manager_inner_t*  manager, 
    data_file_lock_t* lock
) {

    manager->lock_file_handle = fopen(manager->paths.lock_file, "r");
    str_t a = strerror(errno);
    soft_assert_ret_id(
        manager->lock_file_handle != INVALID_HNDL, 
        "Opening main app lock file failed: (%s)!", 
        strerror(errno)
    );

    fgets((bytes_t)lock, sizeof(data_file_lock_t), manager->lock_file_handle);

    soft_assert_ret_id(
        fclose(manager->lock_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return;
}


bool_t data_manager_lock(data_manager_inner_t* manager) {

    bool_t first_time   = B_True;
    data_file_lock_t lock = {0};
    data_manager_get_lock(manager, &lock);

    loop {

        if (lock.is_locked) {

            if (first_time) {
                printf(DNG_TXT("Blocked! waiting...")"\n");
                printf(TRANSPARENT_TXT("NOTE: Another Clocker app is running on your system!\n"\
                    TRANSPARENT_TXT("If you want to make this one running, run `clocker --no-save`\n")\
                ));
                first_time = B_False;
            }

            data_manager_get_lock(manager, &lock);
            sleep(5);
        }

        else {

            manager->lock_file_handle = fopen(manager->paths.lock_file, "w");
            soft_assert_ret_id(
                manager->lock_file_handle != INVALID_HNDL, 
                "Failed to open lock file: (%s)!",
                strerror(errno)
            );

            lock.state     = (lock.state == DFS_Nothing) ? DFS_NotSaved : lock.state;
            lock.is_locked = B_True;

            for (index_t idx = 0; idx < sizeof(data_file_lock_t); idx++) {
                fputc(((bytes_t)&lock)[idx], manager->lock_file_handle);
            }

            break;
        }
    }

    soft_assert_ret_id(
        fclose(manager->lock_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return B_True;
}


bool_t data_manager_unlock(data_manager_inner_t* manager) {

    manager->lock_file_handle = fopen(manager->paths.lock_file, "w");
    soft_assert_ret_id(
        manager->lock_file_handle != INVALID_HNDL, 
        "Failed to open main app lock file: (%s)!",
        strerror(errno)
    );

    data_file_lock_t lock = {
        .state     = DFS_Saved,
        .is_locked = B_False
    };

    for (index_t idx = 0; idx < sizeof(data_file_lock_t); idx++) {
        fputc(((bytes_t)&lock)[idx], manager->lock_file_handle);
    }

    soft_assert_ret_id(
        fclose(manager->lock_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return B_True;
}


bool_t data_manager_read_data(data_manager_inner_t* manager) {

    manager->data_file_handle = fopen(manager->paths.data_file, "r");
    soft_assert_ret_id(
        manager->data_file_handle != INVALID_HNDL, 
        "Opening main app data file failed: (%s)!", 
        strerror(errno)
    );

    data_file_data_t data = {0};
    fgets((bytes_t)& data, sizeof(data_file_data_t), manager->data_file_handle);
    
    manager->timer = timer_new();
    timer_init(&manager->timer, data.total, data.final);
    soft_assert_ret_id(boxed_unbox(&manager->timer.inner) != INVALID_HNDL, "Initializing new timer failed!");

    soft_assert_ret_id(
        fclose(manager->data_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return B_True;
}


PUB
bool_t data_manager_save_data(
    data_manager_t*   manager, 
    clocker_timer_t* timer, 
    bool_t           final
) {

    time_eval_t     time    = {0};
    data_manager_inner_t* _manager = (data_manager_inner_t*) boxed_unbox(&manager->inner);

    _manager->data_file_handle = fopen(_manager->paths.data_file, "w");
    soft_assert_ret_id(
        _manager->data_file_handle != INVALID_HNDL, 
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
        fputc(((bytes_t)&data)[idx], _manager->data_file_handle);
    }
    
    
    soft_assert_ret_id(
        fclose(_manager->data_file_handle) == 0,
        "Failed to close lock file: (%s)!",
        strerror(errno)
    );

    return B_True;
}


bool_t data_manager_clear_data(data_manager_inner_t* manager) {
    manager->timer = timer_new();
    soft_assert_ret_id(boxed_unbox(&manager->timer.inner) != INVALID_HNDL, "Creating new timer failed!");

    return B_True;
}


PUB
data_manager_t data_manager_start(bool_t no_save) {

    boxed_t boxed = boxed_new(sizeof(data_manager_inner_t));
    soft_assert_ret(boxed_unbox(&boxed) != INVALID_HNDL, (data_manager_t) {.inner = 0}, "Creating data_manager boxed pointer failed!");

    data_manager_inner_t* new = (data_manager_inner_t*) boxed_unbox(&boxed);

    paths_get(new);
    new->saving = !no_save;

    if (new->saving) {
        soft_assert_ret(
            data_manager_lock_init(new),
            (data_manager_t) {.inner = 0},
            "Initializing app lock file failed!"
        );

        soft_assert_ret(
            data_manager_lock(new),
            (data_manager_t) {.inner = 0},
            "Initializing app lock file failed!"
        );
    }

    soft_assert_ret(
        data_manager_dir_init(new),
        (data_manager_t) {.inner = 0},
        "Initializing app main directory failed!"
    );

    soft_assert_ret(
        data_manager_file_init(new),
        (data_manager_t) {.inner = 0},
        "Initializing app data file failed!"
    );

    data_file_lock_t lock = {0};
    data_manager_get_lock(new, &lock);
    
    if (lock.state != DFS_Nothing && new->saving) {
        printf(INF_TXT("There are some data from last time Clocker was run.\n"\
              "Do you want to resotre and continue that?[Y/n]")
        );

        char_t result = fgetc(stdin);
        if (result == '\n' || result == 'Y' || result == 'y') {
            soft_assert_ret(
                data_manager_read_data(new),
                (data_manager_t) {.inner = 0},
                "Reading data failed!"
            );

            return (data_manager_t) (data_manager_t) {.inner = boxed};
        }
    }

    soft_assert_ret(
        data_manager_clear_data(new),
        (data_manager_t) {.inner = 0},
        "Clearing data failed!"
    );
        
    return (data_manager_t) (data_manager_t) {.inner = boxed};
}


PUB
void_t data_manager_stop(data_manager_t manager, clocker_timer_t* timer) {

    data_manager_inner_t* _manager = (data_manager_inner_t*) boxed_unbox(&manager.inner);

    if (_manager->saving) {

        soft_assert_ret_void(
            data_manager_save_data(&manager, timer, B_True),
            "Initializing app data file failed!"
        );

        soft_assert_ret_void(
            data_manager_unlock(_manager),
            "Initializing app lock file failed!"
        );
    }

    timer_destroy(_manager->timer);
    boxed_destroy(manager.inner);
}


PUB
clocker_timer_t* data_manager_get_timer(data_manager_t* manager) {
    data_manager_inner_t* _manager = (data_manager_inner_t*) boxed_unbox(&manager->inner);
    return &_manager->timer;
}


PUB
bool_t data_manager_allow_saving(data_manager_t* manager) {
    data_manager_inner_t* _manager = (data_manager_inner_t*) boxed_unbox(&manager->inner);
    return _manager->saving;
}