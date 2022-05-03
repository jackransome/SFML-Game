#include "Event.h"

Event::Event(int _sourceId, EventType _type, float _amount, int _beat, float _phase) {
	sourceId = _sourceId;
	type = _type;
	amount = _amount;
	beat = _beat;
	phase = _phase;
	if (type == test1) {
		hasConditions = false;
	}
	else {
		hasConditions = true;
	}
}

int Event::getBeat() {
	return beat;
}

float Event::getPhase() {
	return phase;
}

bool Event::getHasConditions() {
	return hasConditions;
}

EventType Event::getType() {
	return type;
}
