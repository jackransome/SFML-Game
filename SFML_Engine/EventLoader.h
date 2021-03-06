#pragma once
#include "Condition.h"
#include "Action.h"
#include "EventType.h"

struct EventSounds {
	bool hasStartSound = false;
	bool hasEndSound = false;
	bool hasMiddleSound = false;
	std::string startSound;
	std::string endSound;
	std::string middleSound;
};

struct ConditionList {
	int size;
	Condition* list;
	void addCondition(Condition condition) {
		list[size] = condition;
		size++;
	}
	void initialise(int _size) {
		size = _size;
		list = new Condition[_size];
	}
	bool hasSound;
	std::string soundName = "";
	float amountModifier;
};

struct ActionList {
	int size;
	Action* list;
	void addAction(Action action) {
		list[size] = action;
		size++;
	}
	void initialise(int _size) {
		size = _size;
		list = new Action[_size];
	}
};

struct CAPair {
	bool hasCondition;
	ConditionList conditionList;
	ActionList actionList;
	bool post; //if should be done after or in the middle of the beat
};

struct CAPairList {
	int size;
	CAPair* list;
	void initialise(int _size) {
		size = _size;
		list = new CAPair[_size];
	}
};

class EventLoader {
public:
	EventLoader() {}
	static EventSounds loadEventSounds(EventType type);
	static CAPairList loadCAPairs(EventType type, int sourceId, float amount);
};