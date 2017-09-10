#ifndef TN_EVENT_H
#define TN_EVENT_H

#include <poll.h>
#include <sys/epoll.h>

namespace TinyNet
{
    enum Event
    {
        EVENT_READ = POLLIN,
        EVENT_WRITE = POLLOUT
    };
}

#endif
