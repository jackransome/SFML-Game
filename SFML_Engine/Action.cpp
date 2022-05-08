#include "Action.h"

Action::Action(int _sourceId, ActionType _type, EventType _eventType, int _eventDelay, std::string _soundName, float _amount){
	sourceId = _sourceId;
	type = _type;
	eventType = _eventType;
	eventDelay = _eventDelay;
	soundName = _soundName;
	amount = _amount;
}