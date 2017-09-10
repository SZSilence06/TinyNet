#ifndef TN_POLLER_H
#define TN_POLLER_H

#include <Common.h>
#include <Socket.h>
#include <Buffer.h>
#include <vector>

namespace TinyNet
{
    TN_API class Poller : public NonClonable
    {
    public:
        ~Poller();

        static Poller* create();

        bool addSocket(Socket* socket);

        bool waitEvents();

        void setMaxEvents(int max_events) { max_events_ = max_events; }
        void setMaxTimeout(int max_timeout) { max_timeout_ = max_timeout; }

    private:
        Poller() = default;

        const int DEFAULT_MAX_EVENTS = 4000;
        const int DEFAULT_MAX_TIMEOUT = 50;

    private:
        int epoll_fd_ = -1;
        std::vector<Socket*> living_sockets_;
        Buffer active_buffer_;
        int max_events_ = DEFAULT_MAX_EVENTS;
        int max_timeout_ = DEFAULT_MAX_TIMEOUT;
    };
}

#endif
