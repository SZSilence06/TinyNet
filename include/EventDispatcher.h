#ifndef TN_EVENT_DISPATCHER_H
#define TN_EVENT_DISPATCHER_H

#include <Common.h>
#include <memory>

namespace TinyNet
{
    class Poller;

    class EventDispatcher : public NonClonable
    {
    public:
        EventDispatcher();

        Poller* getPoller() const { return poller_.get(); }

        int run();

    private:
        std::unique_ptr<Poller> poller_;
    };
}

#endif
