
#pragma once

#include "core/util/nonCopyable.h"
#include <windows.h>
#include <functional>
#include <map>

OC_NS_BG;

struct Event;

typedef std::shared_ptr<Event> EventPtr;

struct Event
{
    enum class Type
    {
        WndResize = 0,
        KeyDown,
        KeyUp,
        MouseDown,
        MouseUp
    };

    typedef std::function<void(EventPtr)> Callback;

    String m_name;
    Type m_type;

protected:
    Event(const String& name, Type type);
};

struct ResizeEvent : public Event
{
    ResizeEvent(uint32 width, uint32 height);

    uint32 m_width;
    uint32 m_height;
};


class EventDispatcher : public NonCopyable
{
public:

    void addEventHandler(Event::Type msgType, Event::Callback callback);
    void removeEventHandler(Event::Type msgType);

    void dispatchEvent(EventPtr event);

private:
    std::map<Event::Type, Event::Callback> m_handlers;
};

OC_NS_END;