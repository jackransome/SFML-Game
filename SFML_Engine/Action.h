#pragma once
#include "EventType.h"
#include <string>
#include "Console.h"

enum ActionType { a_addEvent, a_playSound, a_doAOEDamage50, a_doAOEdamageAtMouse};

class Action {
public:
	Action(){}
	Action(int sourceId, ActionType type, EventType eventType, int eventDelay, std::string soundName, float amount);
	int getSourceId() { return sourceId; };
	ActionType getType() { return type; };
	EventType getEventType() { return eventType; };
	int getEventDelay() { return eventDelay; };
	std::string getSoundName() { return soundName; };
	float getAmount() { return amount; };
private:
	int sourceId;
	ActionType type;
	EventType eventType;
	int eventDelay;
	std::string soundName;
	float amount;
	bool hasCommand;
	Command command;
};