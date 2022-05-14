#pragma once
#include "EventLoader.h"

class Event {
public:
	Event(int _sourceId, EventType _type, float _amount, int _beat);
	int getBeat();
	bool getHasConditions();
	EventType getType();
	CAPairList getCAPairs();
	int getSourceId();
	float getAmount();
private:
	int sourceId;
	EventType type;
	float amount;
	int beat;
	CAPairList CAPairs;
};