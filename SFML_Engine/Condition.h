#pragma once
#include "EventType.h"
#include <string>

class Condition {
public:
	Condition(){}
	Condition(bool _sameSourceId, EventType _eventType);
	Condition(bool _sameSourceId, EventType _eventType, bool _lackOf);
	Condition(bool _sameSourceId, EventType _eventType, bool _lackOf, float _minAmount);
	bool getSameSourceId();
	EventType getEventType();
	float getMinAmount();
	bool getLackOf();
private:
	bool lackOf;
	bool sameSourceId;
	EventType eventType;
	float minAmount;
};