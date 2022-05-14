#include "EventLoader.h"
#include <iostream>

CAPairList EventLoader::loadCAPairs(EventType type, int sourceId, float amount)
{
	CAPairList list = CAPairList();
	//switch based on event type, fill with pairs inside
	switch (type) {
	case test1:

		list.size = 0;
		break;
	case test2:
		list.pairs[0] = new CAPair();
		list.pairs[0]->hasCondition = true;
		list.pairs[0]->conditionList = ConditionList();
		list.pairs[0]->conditionList.size = 1;
		list.pairs[0]->conditionList.list[0] = new Condition(true, test1);
		list.pairs[0]->conditionList.soundName = "ex5";
		list.pairs[0]->actionList = ActionList();
		list.pairs[0]->actionList.size = 1;
		list.pairs[0]->actionList.list[0] = new Action(sourceId, a_addEvent, test2, 2, "", 1);
		list.size = 1;
		break;
	case test3:
		list.pairs[0] = new CAPair();
		list.pairs[0]->hasCondition = true;
		list.pairs[0]->conditionList = ConditionList();
		list.pairs[0]->conditionList.size = 2;
		list.pairs[0]->conditionList.list[0] = new Condition(true, test1, true);
		list.pairs[0]->conditionList.list[1] = new Condition(true, test3, false, 0.2);
		list.pairs[0]->conditionList.amountModifier = 0.5;
		//list.pairs[0]->conditionList.soundName = "1";
		list.pairs[0]->actionList = ActionList();
		list.pairs[0]->actionList.size = 1;
		list.pairs[0]->actionList.list[0] = new Action(sourceId, a_addEvent, test3, 2, "", amount);
		list.size = 1;
		break;
	}
	return list;
}
