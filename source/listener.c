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

#include "framework/prims/inc.h"
#include "includes/listener.h"

typedef struct passwd passwd_t;
typedef struct stat   stat_t;
typedef struct dirent dirnet_t;
typedef struct pollfd pollfd_t;

typedef  pthread_t Thread;


typedef struct {
    i64_t  input_file;
    bool_t fired;
}
event_listener_t;


typedef struct {
    event_listener_t mouse;
    event_listener_t keyboard;
    bool_t           flag;
    nfds_t           nfds;
    UNSAFE pollfd_t  fds[2];
}
listener_inner_t;


listener_t listener_new() {
    listener_inner_t* new = (listener_inner_t*) malloc(sizeof(listener_inner_t));
    soft_assert_ret(new, (listener_t) {.inner = 0}, "Allocating new listener failed!");

    dirnet_t* dir_net = {0};     
    DIR* dir = opendir ("/dev/input/by-path");
    soft_assert_ret(
        dir != INVALID_HNDL,
         (listener_t) {.inner = 0},
        "Opening /dev/input/by-path/ failed! (%s)", 
        strerror(errno)
    );

    while (dir_net = readdir(dir)) {

        if (*(dir_net->d_name) != '.') {

            char_t buff[2048] = {0};
            sprintf(buff, "/dev/input/by-path/%s", dir_net->d_name);

            if (strstr(dir_net->d_name, "event-mouse") != INVALID_HNDL) {
                new->mouse.input_file = open(buff, O_RDONLY);
                soft_assert_ret(
                    new->mouse.input_file != -1, 
                    (listener_t) {.inner = 0},
                    "Opening mouse input file failed: %s", 
                    strerror(errno)
                );
            }
            
            if (strstr(dir_net->d_name, "kbd") != INVALID_HNDL) {
                new->keyboard.input_file = open(buff, O_RDONLY);
                soft_assert_ret(
                    new->keyboard.input_file != -1,
                    (listener_t) {.inner = 0},
                    "Opening keyboard input file failed: %s", 
                    strerror(errno)
                );
            }
        }
    }

    soft_assert_ret(
        closedir(dir) == 0,
        (listener_t) {.inner = 0},
        "Closing directory failed! (%s)",
        strerror(errno)
    );

    new->keyboard.fired = B_True;
    new->mouse.fired    = B_True;
    new->flag           = B_False;

    new->fds[0].fd = new->keyboard.input_file;
    new->fds[0].events = POLLIN;

    new->fds[1].fd = new->mouse.input_file;
    new->fds[1].events = POLLIN;

    new->nfds = 2;

    return (listener_t) {.inner = (u64_t) new};
}


void_t listener_listen(listener_t* listener) {

    Thread mouse_thrd    = 0;
    Thread keyboard_thrd = 0;

    listener_inner_t* _listener = (listener_inner_t*) listener->inner;
    size_t counter = 0;

    loop {
        int poll_num = poll(_listener->fds, _listener->nfds, 1000);
        if (poll_num == 0) {
            char_t dot_cont[32] = {0};
            if (counter >= 120) {
                sprintf(dot_cont, "\r"TRANSPARENT_TXT("idle (%lds)")" > ", counter - 120);
                write(STDOUT_FILENO, "                               ", 32);
                write(STDOUT_FILENO, dot_cont, 32);
            }
            counter++;
            continue;
        }

        char_t buff[1024] = {0};
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


i64_t listener_fired(listener_t* listener) {
    listener_inner_t* _listener = (listener_inner_t*) listener->inner;
    return (_listener->keyboard.fired || _listener->mouse.fired);
}


i64_t listener_drop(listener_t listener) {
    listener_inner_t* _listener = (listener_inner_t*) listener.inner;
    free(_listener);
}