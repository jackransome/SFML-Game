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
	case test4:
		//2 pairs, one is no test1, modifier 0.5
		// one is with test1, modifier is 2
		list.size = 2;
		list.pairs[0] = new CAPair();
		list.pairs[0]->hasCondition = true;
		list.pairs[0]->conditionList = ConditionList();
		list.pairs[0]->conditionList.size = 2;
		list.pairs[0]->conditionList.list[0] = new Condition(true, test1, true);
		list.pairs[0]->conditionList.list[1] = new Condition(true, test4, false, 0.2);
		list.pairs[0]->conditionList.amountModifier = 0.5;
		//list.pairs[0]->conditionList.soundName = "1";
		list.pairs[0]->actionList = ActionList();
		list.pairs[0]->actionList.size = 1;
		list.pairs[0]->actionList.list[0] = new Action(sourceId, a_addEvent, test4, 2, "", amount);
		list.pairs[1] = new CAPair();
		list.pairs[1]->hasCondition = true;
		list.pairs[1]->conditionList = ConditionList();
		list.pairs[1]->conditionList.size = 2;
		list.pairs[1]->conditionList.list[0] = new Condition(true, test1, false);
		list.pairs[1]->conditionList.list[1] = new Condition(true, test4, false, 0.2);
		list.pairs[1]->conditionList.amountModifier = 2;
		//list.pairs[0]->conditionList.soundName = "1";
		list.pairs[1]->actionList = ActionList();
		list.pairs[1]->actionList.size = 1;
		list.pairs[1]->actionList.list[0] = new Action(sourceId, a_addEvent, test4, 2, "", amount);	
		break;
	}
	return list;
}
