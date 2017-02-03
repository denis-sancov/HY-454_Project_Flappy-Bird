//
// Created by Denis Sancov on 14/11/2016.
//

#ifndef PROJECT_HY454_EVENT_H
#define PROJECT_HY454_EVENT_H

#include <memory>
#include "Geometry.h"

namespace csd {

    class Event {
    public:
        typedef enum _type {
            Unrecognized = 0,
            PressedDown,
            PressedUp
        } EventType;

        virtual ~Event() {}

        EventType getEvent() const { return _eventType; }

    private:
        const EventType _eventType;
    protected:
        Event(EventType type): _eventType(type) { }
    };

    class TerminateGameEvent : public Event {
    public:
        TerminateGameEvent():Event(Unrecognized) { }
    };


    class MouseEvent : public Event {
    public:
        MouseEvent(EventType type, Point mousePosition):Event(type), _mousePosition(mousePosition) {}
        Point getPosition() const { return  _mousePosition; }
    private:
        const Point _mousePosition;
    };

    class KeyboardEvent: public Event {
    public:
        KeyboardEvent(EventType type, unsigned int keyCode):Event(type), _keyCode(keyCode) {}
        unsigned int keyCode() const { return _keyCode; }
    private:
        unsigned int const _keyCode;
    };

    class EventHandler {
        virtual void handleEvent(std::shared_ptr<Event> const eventPtr) = 0;
    };
}


#endif //PROJECT_HY454_EVENT_H
