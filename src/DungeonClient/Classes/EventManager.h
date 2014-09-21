#pragma once
#include "Event.h"
#include "EventListener.h"
#include <map>
class EventManager
{
public:
	static EventManager* GetInstance()
	{
		if (pInstance_ == nullptr)
		{
			pInstance_ = new EventManager;
		}
		return pInstance_;
	}
	static void FreeInstance()
	{
		if (pInstance_ != nullptr)
		{
			delete pInstance_;
			pInstance_ = nullptr;
		}
	}


	void AddEventListener(EventTypes event_type, EventListener* listener);
	void RemoveEventListener(EventTypes event_type, EventListener* listener);
	void RemoveEventListener(EventListener* listener);
	void Notify(EventHeader* event);

private:
	EventManager(void);
	~EventManager(void);




private:
	std::multimap<EventTypes, EventListener*> event_listener_list;
	static EventManager* pInstance_;

};
