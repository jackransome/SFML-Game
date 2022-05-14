#include "Condition.h"

Condition::Condition(bool _sameSourceId, EventType _eventType){
	sameSourceId = _sameSourceId;
	eventType = _eventType;
	minAmount = 0;
	lackOf = false;
}

Condition::Condition(bool _sameSourceId, EventType _eventType, bool _lackOf) {
	sameSourceId = _sameSourceId;
	eventType = _eventType;
	minAmount = 0;
	lackOf = _lackOf;
}

Condition::Condition(bool _sameSourceId, EventType _eventType, bool _lackOf, float _minAmount) {
	sameSourceId = _sameSourceId;
	eventType = _eventType;
	minAmount = _minAmount;
	lackOf = _lackOf;
}

bool Condition::getSameSourceId() {
	return sameSourceId;
}

EventType Condition::getEventType() {
	return eventType;
}

float Condition::getMinAmount() {
	return minAmount;
}

bool Condition::getLackOf() {
	return lackOf;
}
