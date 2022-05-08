#pragma once
#include "EventType.h"


class Event {
public:
	Event(int _sourceId, EventType _type, float _amount, int _beat, float _phase);
	int getBeat();
	float getPhase();
	bool getHasConditions();
	EventType getType();
private:
	int sourceId;
	EventType type;
	float amount;
	int beat;
	float phase;
	bool hasConditions;
};