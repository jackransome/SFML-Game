#include "Condition.h"

Condition::Condition(bool _sameSourceId, EventType _eventType){
	sameSourceId = _sameSourceId;
	eventType = _eventType;
	minAmount = 0;
}

Condition::Condition(bool _sameSourceId, EventType _eventType, float _minAmount) {
	sameSourceId = _sameSourceId;
	eventType = _eventType;
	minAmount = _minAmount;
}

bool Condition::getSameSourceId() {
	return sameSourceId;
}

EventType Condition::getEventType() {
	return eventType;
}
