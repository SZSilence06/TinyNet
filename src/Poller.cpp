#include <Poller.h>
#include <Logger.h>
#include <sys/epoll.h>
#include <unistd.h>

namespace TinyNet
{ 
    Poller::~Poller()
    {
        if(epoll_fd_ >= 0)
            close(epoll_fd_);
    }

    Poller* Poller::create()
    {
        int epoll_fd = epoll_create1(EPOLL_CLOEXEC);
        if(epoll_fd == -1)
        {
            TN_ERROR("create epoll failed!");
            return nullptr;
        }
        Poller* poller = new Poller();
        poller->epoll_fd_ = epoll_fd;
        if(poller->active_buffer_.resize(poller->max_events_ * sizeof(epoll_event)) == false)
        {
            TN_ERROR("Failed to alloc active buffer for poller!");
            delete poller;
            return nullptr;
        }
        return poller;
    }

    bool Poller::addSocket(Socket *socket)
    {
        if(epoll_fd_ < 0)
        {
            TN_FATAL("Try to add socket to invalid poller!");
            return false;
        }
        struct epoll_event event;
        event.events = socket->getEvents();
        event.data.ptr = socket;
        if(epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, socket->getFd(), &event) == -1)
        {
            TN_ERROR("Fail to add socket to poller!");
            return false;
        }
        living_sockets_.push_back(socket);
        return true;
    }

    bool Poller::waitEvents()
    {
        int active_count = epoll_wait(epoll_fd_, (epoll_event*)active_buffer_.data,
                                      max_events_, max_timeout_);
        if(active_count == -1)
        {
            TN_ERROR("epoll_wait failed!");
            return false;
        }
        struct epoll_event* p = (struct epoll_event*)active_buffer_.data;
        for(int i = 0; i < active_count; i++)
        {
            Socket* socket = static_cast<Socket*>(p[i].data.ptr);
            uint32_t events = p[i].events;
            if(events & POLLIN)
                socket->handleRead();
            else if(events & POLLOUT)
                socket->handleWrite();
        }
        return true;
    }
}
