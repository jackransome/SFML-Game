#pragma once
#include "Condition.h"
#include "Action.h"
#include "EventType.h"


struct ConditionList {
	int size;
	Condition* list[5];
	void addCondition(Condition* condition) {
		list[size] = condition;
		size++;
	}
	std::string soundName = "";
	float amountModifier;
};

struct ActionList {
	int size;
	Action* list[5];
	void addAction(Action* action) {
		list[size] = action;
		size++;
	}
};

struct CAPair {
	bool hasCondition;
	ConditionList conditionList;
	ActionList actionList;
};

struct CAPairList {
	int size;
	CAPair* pairs[5];
};

class EventLoader {
public:
	EventLoader() {}
	static CAPairList loadCAPairs(EventType type, int sourceId, float amount);
};