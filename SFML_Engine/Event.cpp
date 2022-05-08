#include "Event.h"

Event::Event(int _sourceId, EventType _type, float _amount, int _beat) {
	sourceId = _sourceId;
	type = _type;
	amount = _amount;
	beat = _beat;
	conditions = EventLoader::loadConditions(_type, _sourceId);
	actions = EventLoader::loadActions(_type, _sourceId);
	if (conditions.size > 0) {
		hasConditions = true;
	}
	else {
		hasConditions = false;
	}
}

int Event::getBeat() {
	return beat;
}

bool Event::getHasConditions() {
	return hasConditions;
}

EventType Event::getType() {
	return type;
}

ActionList Event::getActions() {
	return actions;
}

ConditionList Event::getConditions() {
	return conditions;
}

int Event::getSourceId() {
	return sourceId;
}
