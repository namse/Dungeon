#pragma once
#include <memory>
enum EventTypes
{
	EVENT_NONE = -1,

} ;

struct EventHeader
{
	EventTypes event_type_;
};

namespace Event
{
	
}