#pragma once
#include "EventType.h"
class Condition {
	Condition(bool _sameSourceId, EventType _eventType);
	bool getSameSourceId();
	EventType getEventType();
private:
	bool sameSourceId;
	EventType eventType;
};
