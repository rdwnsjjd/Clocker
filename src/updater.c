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
    sprintf(buff, "%s/%s", home_dir->pw_dir, ".clocker/clocker.conf");
}


Bool updater_do_update(Updater updater) {

    _Updater* _updater = (_Updater*) updater;

    printf("Updating app...\n");

    Char cmd_buff[2048] = {0};
    sprintf(
        cmd_buff, "wget %s/v%s  -P /root/.clocker/.new --quiet", 
        "https://api.github.com/repos/rdwnsjjd/Clocker/zipball/refs/tags",
        _updater->new_version
    );

    soft_assert_ret_id(
        system(cmd_buff) == 0,
        "Cannot get available version of clocker!"
    );

    memset(cmd_buff, 0, 2048);
    sprintf(
        cmd_buff, "unzip -q /root/.clocker/.new/v%s -d /root/.clocker/.new/source",
        _updater->new_version
    );

    soft_assert_ret_id(
        system(cmd_buff) == 0,
        "Cannot extract source file!"
    );

    Char path_buff[2048] = {0};
    sprintf(
        path_buff, "/root/.clocker/.new/v%s",
        _updater->new_version
    );

    soft_assert_ret_id(
        remove(path_buff) == 0,
        "Cannot remove source zip file!"
    );

    Dirnet* dir_net = {0};     
    DIR* dir = opendir ("/root/.clocker/.new/source");
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
                cmd_buff, "make --file=/root/.clocker/.new/source/%s/makefile all",
                dir_net->d_name
            );

            soft_assert_ret_id(
                system(cmd_buff) == 0,
                "Coping binary failed!"
            );

            memset(cmd_buff, 0, 2048);
            sprintf(
                cmd_buff, 
                "cp /root/.clocker/.new/source/%s/build/clocker /bin/clocker",
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
        system("rm -rf /root/.clocker/.new") == 0,
        "Deleting directory failed!"
    );

    printf("Done!\n");
    return 1;
}

Void main() {

    Str argv[2] = {"/bin/clocker", INVALID_HNDL};

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
    execvp("/bin/clocker", argv);
    return;
}
