#include <EventDispatcher.h>
#include <Poller.h>

namespace TinyNet
{
    EventDispatcher::EventDispatcher()
    {
        poller_.reset(Poller::create());
    }

    int EventDispatcher::run()
    {
        while(true)
        {
            if(poller_->waitEvents() == false)
            {
                return EXIT_FAILURE;
            }
        }
        return 0;
    }
}
