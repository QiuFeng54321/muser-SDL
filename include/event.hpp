#ifndef EVENT_HPP
#define EVENT_HPP

namespace muser::event {
    enum class EventClass {
        kUnknown = -1,
        kMainController,
        kGameEvent
    };
    enum class EventType {
        kUnknown = -1,  // explicit -1 mark
        kGetKeysPressed,
        kKeyPressed,
        kTriggerNoteInRange
    };
    class Event {
        // Data that might be used by derived event classes
        void* data = nullptr;
    public:
        /**
        * @brief the function to be called by the event system.
        * @tparam ret_type return type of call function
        * @tparam ...args_types arg types of call function
        * @param args arguments to be passed in
        * @returns ret_type result to be passed back to the event system
        */
        template <typename ret_type, typename... args_types>
        ret_type Call(args_types&&... args);

        // Class of the event
        static constexpr EventClass kEventClass = EventClass::kUnknown;
        // Type of the event
        static constexpr EventType kType = EventType::kUnknown;
    };

    class TestEvent : Event {
    public:
        int Call(char a, char b);
    };
}  // namespace muser::event

#endif