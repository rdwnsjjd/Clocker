#include "../../headers/listener.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#include <fcntl.h>
#include <poll.h>

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

    new->keyboard.input_file = open("/dev/input/by-path/pci-0000:00:14.0-usb-0:11:1.0-event-kbd", O_RDONLY);
    soft_assert_ret_id(new->keyboard.input_file != -1, "Opening keyboard input file failed: %s", strerror(errno));

    new->mouse.input_file = open("/dev/input/by-path/pci-0000:00:14.0-usb-0:12:1.0-event-mouse", O_RDONLY);
    soft_assert_ret_id(new->mouse.input_file != -1, "Opening mouse input file failed: %s", strerror(errno));

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
            Char dot_cont[16] = {0};
            if (counter >= 120) {
                sprintf(dot_cont, "\rIdel %lds > ", counter - 120);
                write(STDOUT_FILENO, "               ", 16);
                write(STDOUT_FILENO, dot_cont, 16);
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