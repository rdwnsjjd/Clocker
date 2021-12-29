#ifndef HEADERS_LISTENER_H
#define HEADERS_LISTENER_H

#include "../includes/common/inc.h"

typedef UInt64 Listener;


Listener listener_new();

Void listener_listen(Listener listener);

Int64 listener_fired(Listener listener);



#define listener_event_fired(_listener) listener_fired(_listener)

#endif // HEADERS_LISTENER_H