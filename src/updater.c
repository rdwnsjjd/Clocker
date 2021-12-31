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

#include "../includes/common/inc.h"
#include "../headers/updater_checker.h"

typedef struct passwd Passwd;
typedef struct stat   Stat;
typedef struct dirent Dirnet;

typedef struct {
    Str version;
    Str new_version;
}
_Updater;


Str updater_get_conf_file(Str buff) {

    Passwd* home_dir       = getpwuid(getuid());
    sprintf(buff, "%s/%s", home_dir->pw_dir, ".config/clocker/clocker.conf");
}


Bool updater_do_update(Updater updater) {

    _Updater* _updater = (_Updater*) updater;

    printf("Updating app...\n");

    Char cmd_buff[2048] = {0};
    sprintf(
        cmd_buff, "wget %s/v%s  -P /root/.config/clocker/.new --quiet", 
        "https://api.github.com/repos/rdwnsjjd/Clocker/zipball/refs/tags",
        _updater->new_version
    );

    soft_assert_ret_id(
        system(cmd_buff) == 0,
        "Cannot get available version of clocker!"
    );

    memset(cmd_buff, 0, 2048);
    sprintf(
        cmd_buff, "unzip -q /root/.config/clocker/.new/v%s -d /root/.config/clocker/.new/source",
        _updater->new_version
    );

    soft_assert_ret_id(
        system(cmd_buff) == 0,
        "Cannot extract source file!"
    );

    Char path_buff[2048] = {0};
    sprintf(
        path_buff, "/root/.config/clocker/.new/v%s",
        _updater->new_version
    );

    soft_assert_ret_id(
        remove(path_buff) == 0,
        "Cannot remove source zip file!"
    );

    Dirnet* dir_net = {0};     
    DIR* dir = opendir ("/root/.config/clocker/.new/source");
    soft_assert_ret_id(
        dir != INVALID_HNDL, 
        "Opening source directory failed! (%s)", 
        strerror(errno)
    );

    while (dir_net = readdir(dir)) {

        if (*(dir_net->d_name) != '.') {

            memset(path_buff, 0, 2048);
            getcwd(path_buff, 2048);
            strcat(path_buff, "/");

            memset(cmd_buff, 0, 2048);
            sprintf(
                cmd_buff, "make --file=/root/.config/clocker/.new/source/%s/makefile all && clear",
                dir_net->d_name
            );

            soft_assert_ret_id(
                system(cmd_buff) == 0,
                "Coping binary failed!"
            );

            memset(cmd_buff, 0, 2048);
            sprintf(
                cmd_buff, 
                "cp /root/.config/clocker/.new/source/%s/build/clocker /usr/bin/clocker",
                dir_net->d_name
            );

            soft_assert_ret_id(
                system(cmd_buff) == 0,
                "Coping binary failed!"
            );

            memset(path_buff, 0, 2048);
            updater_get_conf_file(path_buff);

            FILE* data_file_ptr = fopen(path_buff, "w");
            soft_assert_ret_id(
                data_file_ptr != INVALID_HNDL,
                "Creating main app data file failed! (%s)",
                strerror(errno)
            );

            fputs(_updater->new_version, data_file_ptr);
            memcpy(_updater->version, _updater->new_version, strlen(_updater->new_version));

            soft_assert_ret_id(
                fclose(data_file_ptr) == 0,
                "Closing main app data failed! (%s)",
                strerror(errno)
            );

            break;
        }
    }

    soft_assert_ret_id(
        closedir(dir) == 0,
        "Closing directory failed! (%s)",
        strerror(errno)
    );

    soft_assert_ret_id(
        system("rm -rf /root/.config/clocker/.new") == 0,
        "Deleting directory failed!"
    );

    printf("Done!\n");
    return 1;
}

Void main(
    Int32 argc,
    Str   args[]
) {

    if (!args[1] || (strcmp(args[1], "--from-clocker") != 0)) {
        printf(COLOR_IN_YELLOW"WARNING"COLOR_RESET WRN_TXT(": Running updater directly not recommended.\n"));
        printf("Please use: "TRANSPARENT_TXT("clocker --update\n"));
        return -1;
    }

    Str argv[2] = {"/usr/bin/clocker", INVALID_HNDL};

    Updater checker = update_checker_new();
    soft_assert_wrn(
        checker != 0,
        "Creating new update object failed!"
    );

    UpdateStatus update_check_res = update_checker_check(checker);
    soft_assert_wrn(
        update_check_res != US_Error,
        "Checking for new version failed!"
    );

    updater_do_update(checker);
    execvp("/usr/bin/clocker", argv);
    return;
}
