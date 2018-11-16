#include "EventHandler.h"
#include "EventBase.h"

void EventHandler::handleEvent(const EventBase *evnt)
{
	auto p = m_delegateMap.find(std::type_index{ typeid(*evnt) });
	if (p != end(m_delegateMap))
		p->second->call(evnt);
}

void EventHandler::broadcastEvent(const EventBase *evnt)
{
	int sz = AutoList<EventHandler>::size();
	for (int i = 0; i < sz; ++i)
	{
		auto p = AutoList<EventHandler>::get(i);
		if (p != this)
			p->handleEvent(evnt);
	}
}