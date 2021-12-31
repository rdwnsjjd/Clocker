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

#include "../../headers/listener.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#include <fcntl.h>
#include <poll.h>

#include <sys/stat.h>
#include <dirent.h>

typedef struct passwd Passwd;
typedef struct stat   Stat;
typedef struct dirent Dirnet;

typedef  pthread_t Thread;


typedef struct {
    Int64 input_file;
    Bool  fired;
}
_EventListener;


typedef struct {
    _EventListener mouse;
    _EventListener keyboard;
    Bool           flag;
    nfds_t         nfds;
    struct pollfd  fds[2];
}
_Listener;


pthread_mutex_t mutex = {0};

Listener listener_new() {
    _Listener* new = (_Listener*) malloc(sizeof(_Listener));
    soft_assert_ret_id(new, "Allocating new listener failed!");

    Dirnet* dir_net = {0};     
    DIR* dir = opendir ("/dev/input/by-path");
    soft_assert_ret_id(
        dir != INVALID_HNDL, 
        "Opening /dev/input/by-path/ failed! (%s)", 
        strerror(errno)
    );

    while (dir_net = readdir(dir)) {

        if (*(dir_net->d_name) != '.') {

            Char buff[2048] = {0};
            sprintf(buff, "/dev/input/by-path/%s", dir_net->d_name);

            if (strstr(dir_net->d_name, "event-mouse") != INVALID_HNDL) {
                new->mouse.input_file = open(buff, O_RDONLY);
                soft_assert_ret_id(
                    new->mouse.input_file != -1, 
                    "Opening mouse input file failed: %s", 
                    strerror(errno)
                );
            }
            
            if (strstr(dir_net->d_name, "kbd") != INVALID_HNDL) {
                new->keyboard.input_file = open(buff, O_RDONLY);
                soft_assert_ret_id(
                    new->keyboard.input_file != -1, 
                    "Opening keyboard input file failed: %s", 
                    strerror(errno)
                );
            }
        }
    }

    soft_assert_ret_id(
        closedir(dir) == 0,
        "Closing directory failed! (%s)",
        strerror(errno)
    );

    new->keyboard.fired = True;
    new->mouse.fired    = True;
    new->flag           = False;

    new->fds[0].fd = new->keyboard.input_file;
    new->fds[0].events = POLLIN;

    new->fds[1].fd = new->mouse.input_file;
    new->fds[1].events = POLLIN;

    new->nfds = 2;

    pthread_mutex_init(&mutex, INVALID_HNDL);

    return (Listener) new;
}


Void listener_listen(Listener listener) {

    Thread mouse_thrd    = 0;
    Thread keyboard_thrd = 0;

    _Listener* _listener = (_Listener*) listener;

    Size counter = 0;

    loop {

        int poll_num = poll(_listener->fds, _listener->nfds, 1000);
        if (poll_num == 0) {
            Char dot_cont[32] = {0};
            if (counter >= 120) {
                sprintf(dot_cont, "\r"TRANSPARENT_TXT("idle (%lds)")" > ", counter - 120);
                write(STDOUT_FILENO, "                               ", 32);
                write(STDOUT_FILENO, dot_cont, 32);
            }
            counter++;
            continue;
        }

        Char buff[1024] = {0};
        if (_listener->fds[0].revents & POLLIN) {
            read(_listener->fds[0].fd, buff, 1024);
        }
        else {
            read(_listener->fds[1].fd, buff, 1024);
        }

        // printf(">%ld: \n", counter);

        return;
    }
}


Int64 listener_fired(Listener listener) {
    _Listener* _listener = (_Listener*) listener;
    return (_listener->keyboard.fired || _listener->mouse.fired);
}