#include "EventLoader.h"
#include <iostream>

ConditionList EventLoader::loadConditions(EventType type, int sourceId){
	ConditionList conditionList = ConditionList();
	switch (type) {
	case test1:
		conditionList.size = 0;
		break;
	case test2:
		conditionList.size = 1;
		conditionList.list[0] = Condition(true, test1);
		break;
	}
	return conditionList;
}

ActionList EventLoader::loadActions(EventType type, int sourceId) {
	ActionList actionList = ActionList();
	switch (type) {
	case test1:
		actionList.size = 0;
		break;
	case test2:
		actionList.size = 1;
		actionList.list[0] = Action(sourceId, addEvent, test2, 2, "", 1);
		break;
	}
	return actionList;
}