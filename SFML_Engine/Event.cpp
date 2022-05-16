#include "Event.h"

Event::Event(int _sourceId, EventType _type, float _amount, int _beat) {
	sourceId = _sourceId;
	type = _type;
	amount = _amount;
	beat = _beat;
	CAPairs = EventLoader::loadCAPairs(_type, _sourceId, amount);
	activated = false;
}

int Event::getBeat() {
	return beat;
}

EventType Event::getType() {
	return type;
}

CAPairList Event::getCAPairs() {
	return CAPairs;
}

int Event::getSourceId() {
	return sourceId;
}

float Event::getAmount() {
	return amount;
}

bool Event::getActivated() {
	return activated;
}

void Event::setActivated(bool _activated) {
	activated = _activated;
}