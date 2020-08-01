#include "event.hpp"

namespace muser::event {
    int TestEvent::Call(char a, char b) {
        return a + b;
    }
}  // namespace muser::event
