#pragma once
#include "EventType.h"
class Condition {
public:
	Condition(){}
	Condition(bool _sameSourceId, EventType _eventType);
	Condition(bool _sameSourceId, EventType _eventType, float _minAmount);
	bool getSameSourceId();
	EventType getEventType();
	float getMinAmount();
private:
	bool sameSourceId;
	EventType eventType;
	float minAmount;
};
