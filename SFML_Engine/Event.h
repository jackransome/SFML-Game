#pragma once
#include "EventLoader.h"

class Event {
public:
	Event(int _sourceId, EventType _type, float _amount, int _beat);
	int getBeat();
	bool getHasConditions();
	EventType getType();
	ActionList getActions();
	ConditionList getConditions();
	int getSourceId();
private:
	int sourceId;
	EventType type;
	float amount;
	int beat;
	bool hasConditions;
	ConditionList conditions;
	ActionList actions;
};