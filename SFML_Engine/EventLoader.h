#pragma once
#include "Condition.h"
#include "Action.h"
#include "EventType.h"

struct ConditionList {
	ConditionList() {}
	int size;
	Condition list[5];
};

struct ActionList {
	int size;
	Action list[5];
};

class EventLoader {
public:
	EventLoader() {}
	static ConditionList loadConditions(EventType type, int sourceId);
	static ActionList loadActions(EventType type, int sourceId);
};