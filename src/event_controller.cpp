#include "event_controller.hpp"

namespace muser::event {
    TestEventController::TestEventController() {
        this->events.push_back((Event*)new TestEvent);
    }
    void TestEventController::Call() {
        for (auto e : this->events) {
            std::cout << ((TestEvent*)e)->Call('a', 'b') << std::endl;
        }
    }
}  // namespace muser::event
