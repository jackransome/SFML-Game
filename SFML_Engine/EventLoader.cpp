#include "EventLoader.h"
#include <iostream>

CAPairList EventLoader::loadCAPairs(EventType type, int sourceId, float amount)
{
	CAPairList list = CAPairList();
	//switch based on event type, fill with pairs inside
	switch (type) {
	case test1:
		list.pairs[0] = new CAPair();
		list.pairs[0]->hasCondition = false;
		list.pairs[0]->actionList = ActionList();
		list.pairs[0]->actionList.size = 1;
		list.pairs[0]->actionList.list[0] = new Action(sourceId, a_playSound, test1, 0, "hh", 1);
		list.pairs[0]->post = false;
		list.size = 1;
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
		list.pairs[0]->post = true;

		list.pairs[1] = new CAPair();
		list.pairs[1]->hasCondition = false;
		list.pairs[1]->actionList = ActionList();
		list.pairs[1]->actionList.size = 1;
		list.pairs[1]->actionList.list[0] = new Action(sourceId, a_playSound, test2, 2, "ohh", 1);
		list.pairs[1]->post = false;

		list.size = 2;
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
		list.pairs[0]->post = true;

		list.pairs[1] = new CAPair();
		list.pairs[1]->hasCondition = false;
		list.pairs[1]->actionList = ActionList();
		list.pairs[1]->actionList.size = 1;
		list.pairs[1]->actionList.list[0] = new Action(sourceId, a_playSound, test3, 2, "1", 1);
		list.pairs[1]->post = false;

		list.size = 2;
		break;
	case test4:
		//2 pairs, one is no test1, modifier 0.5
		// one is with test1, modifier is 2
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
		list.pairs[0]->post = true;
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
		list.pairs[1]->post = true;

		list.pairs[2] = new CAPair();
		list.pairs[2]->hasCondition = false;
		list.pairs[2]->actionList = ActionList();
		list.pairs[2]->actionList.size = 1;
		list.pairs[2]->actionList.list[0] = new Action(sourceId, a_playSound, test4, 2, "8tom", 1);
		list.pairs[2]->post = false;

		list.size = 3;

		break;
	}
	return list;
}
