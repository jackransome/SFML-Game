#include "EventLoader.h"
#include <iostream>

CAPairList EventLoader::loadCAPairs(EventType type, int sourceId, float amount)
{
	CAPairList pairList = CAPairList();
	//switch based on event type, fill with pairs inside
	switch (type) {
	case test1:
		pairList.initialise(2);
		pairList.list[0] = CAPair();
		pairList.list[0].hasCondition = false;
		pairList.list[0].actionList = ActionList();
		pairList.list[0].actionList.size = 1;
		pairList.list[0].actionList.initialise(1);
		pairList.list[0].actionList.list[0] = Action(sourceId, a_playSound, test1, 0, "hh", 1);
		pairList.list[0].post = false;

		pairList.list[1] = CAPair();
		pairList.list[1].hasCondition = true;
		pairList.list[1].conditionList = ConditionList();
		pairList.list[1].conditionList.initialise(1);
		pairList.list[1].conditionList.list[0] = Condition(true, test3, false);
		pairList.list[1].conditionList.amountModifier = 2;
		//list.list[0].conditionList.soundName = "1";
		pairList.list[1].actionList = ActionList();
		pairList.list[1].actionList.initialise(1);
		pairList.list[1].actionList.list[0] = Action(sourceId, a_doAOEDamage50, test1, 2, "", amount);
		pairList.list[1].post = false;
		break;
	case test2:
		pairList.initialise(2);
		pairList.list[0] = CAPair();
		pairList.list[0].hasCondition = true;
		pairList.list[0].conditionList = ConditionList();
		pairList.list[0].conditionList.initialise(1);;
		pairList.list[0].conditionList.list[0] = Condition(true, test1);
		pairList.list[0].conditionList.soundName = "ex5";
		pairList.list[0].actionList = ActionList();
		pairList.list[0].actionList.initialise(1);
		pairList.list[0].actionList.list[0] = Action(sourceId, a_addEvent, test2, 2, "", 1);
		pairList.list[0].post = true;

		pairList.list[1] = CAPair();
		pairList.list[1].hasCondition = false;
		pairList.list[1].actionList = ActionList();
		pairList.list[1].actionList.size = 1;
		pairList.list[1].actionList.initialise(1);
		pairList.list[1].actionList.list[0] = Action(sourceId, a_playSound, test2, 2, "ohh", 1);
		pairList.list[1].post = false;
		break;
	case test3:
		pairList.initialise(2);
		pairList.list[0] = CAPair();
		pairList.list[0].hasCondition = true;
		pairList.list[0].conditionList = ConditionList();
		pairList.list[0].conditionList.initialise(2);
		pairList.list[0].conditionList.list[0] = Condition(true, test1, true);
		pairList.list[0].conditionList.list[1] = Condition(true, test3, false, 0.2);
		pairList.list[0].conditionList.amountModifier = 0.5;
		//list.list[0].conditionList.soundName = "1";
		pairList.list[0].actionList = ActionList();
		pairList.list[0].actionList.initialise(1);
		pairList.list[0].actionList.list[0] = Action(sourceId, a_addEvent, test3, 2, "", amount);
		pairList.list[0].post = true;

		pairList.list[1] = CAPair();
		pairList.list[1].hasCondition = false;
		pairList.list[1].actionList = ActionList();
		pairList.list[1].actionList.initialise(1);
		pairList.list[1].actionList.list[0] = Action(sourceId, a_playSound, test3, 2, "1", 1);
		pairList.list[1].post = false;
		break;
	case test4:
		//2 pairs, one is no test1, modifier 0.5
		// one is with test1, modifier is 2
		pairList.initialise(3);
		pairList.list[0] = CAPair();
		pairList.list[0].hasCondition = true;
		pairList.list[0].conditionList = ConditionList();
		pairList.list[0].conditionList.initialise(2);
		pairList.list[0].conditionList.list[0] = Condition(true, test1, true);
		pairList.list[0].conditionList.list[1] = Condition(true, test4, false, 0.2);
		pairList.list[0].conditionList.amountModifier = 0.5;
		//list.list[0].conditionList.soundName = "1";
		pairList.list[0].actionList = ActionList();
		pairList.list[0].actionList.initialise(1);
		pairList.list[0].actionList.list[0] = Action(sourceId, a_addEvent, test4, 2, "", amount);
		pairList.list[0].post = true;
		pairList.list[1] = CAPair();
		pairList.list[1].hasCondition = true;
		pairList.list[1].conditionList = ConditionList();
		pairList.list[1].conditionList.initialise(2);
		pairList.list[1].conditionList.list[0] = Condition(true, test1, false);
		pairList.list[1].conditionList.list[1] = Condition(true, test4, false, 0.2);
		pairList.list[1].conditionList.amountModifier = 2;
		//list.list[0].conditionList.soundName = "1";
		pairList.list[1].actionList = ActionList();
		pairList.list[1].actionList.initialise(1);
		pairList.list[1].actionList.list[0] = Action(sourceId, a_addEvent, test4, 2, "", amount);
		pairList.list[1].post = true;

		pairList.list[2] = CAPair();
		pairList.list[2].hasCondition = false;
		pairList.list[2].actionList = ActionList();
		pairList.list[2].actionList.initialise(1);
		pairList.list[2].actionList.list[0] = Action(sourceId, a_playSound, test4, 2, "8tom", 1);
		pairList.list[2].post = false;
		break;
	}
	return pairList;
}
