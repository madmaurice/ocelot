
#include "event.h"

OC_NS_BG;

Event::Event(const String& name, Type type)
    : m_name(name)
    , m_type(type)
{
}

ResizeEvent::ResizeEvent(uint32 width, uint32 height)
    : Event("Resize", Type::WndResize)
    , m_width(width)
    , m_height(height)
{
}

void EventDispatcher::addEventHandler(Event::Type msgType, Event::Callback callback)
{
    OC_ASSERT_MSG(m_handlers.count(msgType) == 0, "Handler already exist!");
    m_handlers[msgType] = callback;
}

void EventDispatcher::removeEventHandler(Event::Type msgType)
{
    OC_ASSERT_MSG(m_handlers.count(msgType), "Handler doesn't exist!");
    m_handlers.erase(msgType);
}

void EventDispatcher::dispatchEvent(EventPtr event)
{
    std::map<Event::Type, Event::Callback>::iterator it = m_handlers.find(event->m_type);
    if (it != m_handlers.end())
    {
        it->second(event);
    }
}

OC_NS_END;