#pragma once

#include <memory>
#include <typeindex>
#include <map>

#include "AutoList.h"

struct EventBase;

template<typename T, typename EventT>
using MFunc = void(T::*)(const EventT *);

class IDelegate
{
public:
	virtual void call(const EventBase *) = 0;
};

template<typename T, typename EventT>
class Delegate : public IDelegate
{
public:
	Delegate(T *instance, MFunc<T, EventT> func) :
		m_instance{ instance }, m_func{ func }
	{}
	void call(const EventBase *evnt) override
	{
		(m_instance->*m_func)(static_cast<const EventT *>(evnt));
	}
private:
	T *m_instance;
	MFunc<T, EventT> m_func;
};

class EventHandler : public AutoList<EventHandler>
{
public:
	template<typename T, typename EventT>
	void registerFunc(T *instance, MFunc<T, EventT> func)
	{
		m_delegateMap[std::type_index{ typeid(EventT) }] =
			std::make_unique<Delegate<T, EventT>>(instance, func);
	}
	void handleEvent(const EventBase *);
	void broadcastEvent(const EventBase *);
private:
	std::map<std::type_index, std::unique_ptr<IDelegate>> m_delegateMap;
};