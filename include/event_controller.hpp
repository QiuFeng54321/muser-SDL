#ifndef EVENT_CONTROLLER_HPP
#define EVENT_CONTROLLER_HPP

#include <list>

#include "event.hpp"
#include <iostream>

namespace muser::event {
    class EventController {
    public:
        std::list<Event*> events;
        virtual void Call(){};
    };

    class TestEventController : EventController {
    public:
        TestEventController();
        void Call() override;
    };
}  // namespace muser::event

#endif