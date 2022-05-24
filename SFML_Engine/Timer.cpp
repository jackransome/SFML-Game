#include "Timer.h"
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std::chrono;

Timer::Timer(int _bpm, Console* _console){
	changeBpm(_bpm);
	console = _console;
	beat = 0;
	phase = 0;
	startTime = now = getCurrentTime();
}

void Timer::update(){
	now = getCurrentTime() - startTime;;
	
	beat = now / msInOneBeat;
	lastPhase = phase;
	phase = (float)(now % msInOneBeat) / (float)msInOneBeat;
	//std::cout << beat << " b / p " << phase << "\n";
	if (lastPhase < 0.5f && phase >= 0.5f) {
		if (beat % 2 == 0) {
			console->addCommand(commandPlaySound, "sh", 0.1);
		}
		
		console->addCommand(commandPlaySound, "hh4", 0.05);
		//console->addCommand(commandDrawGreenRect);
	}
	for (int i = 0; i < events.size(); i++) {
		
		//middle of beat, for doing things and playing sounds. also making sure it hasnt already been activated (from beatdelay0, from user input)
		if (events[i]->getBeat() == beat && !events[i]->getActivated()) {
			if (lastPhase < 0.5f && phase >= 0.5f) {
				console->addCommand(commandAddObject, objectAction1animation, 30, 100);
				runPairs(events[i], false, false);
			}
		}
		// end of beat, for adding new events
		if (events[i]->getBeat() < beat) {	
			runPairs(events[i], true, false);
		}
	}
	//delete old events
	for (int i = 0; i < events.size(); i++) {
		if (events[i]->getBeat() < beat) {
			events.erase(events.begin() + i);
			i--;
		}
	}
	//clearing events added this beat (for input issues, stopping multiple from being added at once)
	if (lastPhase > 0.5f && phase < 0.5f) {
		addedThisBeat.clear();
	}
}

void Timer::changeBpm(int _bpm) {
	bpm = _bpm;
	msInOneBeat = 60000 / bpm;
}

void Timer::addEvent(int beatDelay, EventType type, int sourceId, float amount, bool accuracy){
	for (int i = 0; i < addedThisBeat.size(); i++) {
		if (addedThisBeat[i] == type) {
			std::cout << "event already added this beat\n";
			return;
		}
	}
	addedThisBeat.push_back(type);
	float newAmount = amount;
	if (accuracy) {
		phase = (float)(now % msInOneBeat) / (float)msInOneBeat;
		float difference = 1 - (2 * abs(phase - 0.5));
		newAmount *= difference;
		std::cout << "accuracy: " << difference << "\n";
	}
	
	events.push_back(new Event(sourceId, type, newAmount, beat + beatDelay));
	//if beat delay is 0 then its intended for this beat so mark it activated and then execute the pairs
	if (beatDelay == 0) {
		events[events.size() - 1]->setActivated(true);
		runPairs(events[events.size() - 1], false, true);
		console->addCommand(commandAddObject, objectAction1animation, 300, 100);
	}
	std::cout << "added event to beat" << beat + beatDelay << "\n";
}

bool Timer::checkConditionList(ConditionList conditionList, int sourceId, bool sameBeat) {
	bool fulfilled = true;
	bool individualFulfilled;
	for (int k = 0; k < conditionList.size; k++) {
		if (conditionList.list[k].getLackOf()) {
			individualFulfilled = true;;
		}
		else {
			individualFulfilled = false;
		}
		EventType eType = conditionList.list[k].getEventType();
		bool sameSourceId = conditionList.list[k].getSameSourceId();
		for (int l = 0; l < events.size(); l++) {
			//checking if event that happened in the beat just finished matches the condition
			if (((events[l]->getBeat() == beat - 1 && !sameBeat) || (events[l]->getBeat() == beat && sameBeat)) && events[l]->getType() == eType) {
				//checking for if needs same source id of not, also checking min amount against amount
				if ((sameSourceId || sourceId == events[l]->getSourceId()) && conditionList.list[k].getMinAmount() <= events[l]->getAmount()) {
					if (conditionList.list[k].getLackOf()) {
						fulfilled = false;
						break;
					}
					individualFulfilled = true;
				}
			}
		}
		if (!individualFulfilled) {
			fulfilled = false;
			break;
		}
	}
	return fulfilled;
}

void Timer::doActionList(CAPair* _CAPair, float amount) {
	ActionList actionList = _CAPair->actionList;
	for (int k = 0; k < actionList.size; k++) {
		switch (actionList.list[k].getType()) {
		case a_addEvent:
			addEvent(actionList.list[k].getEventDelay(), actionList.list[k].getEventType(), actionList.list[k].getSourceId(), actionList.list[k].getAmount() * _CAPair->conditionList.amountModifier, false);
			
			break;
		case a_playSound:
			console->addCommand(commandPlaySound, actionList.list[k].getSoundName());
			break;

		case a_doAOEDamage50:
			console->addCommand(commandDoAEODamage, 0, 0, 50, 10);
			break;

		case a_doAOEdamageAtMouse:
			console->addCommand(commandDamageAtMouse, amount * _CAPair->conditionList.amountModifier);
			break;
		}
	}
}

int Timer::getCurrentTime() {
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Timer::runPairs(Event* event, bool post, bool sameBeat) {
	int fulfilledCount = 0;
	bool runActions = true;
	CAPairList capl = event->getCAPairs();
	// loop thru pairs
	for (int j = 0; j < capl.size; j++) {
		//make sure the pair is / is not for post
		if (capl.list[j].post == post) {
			//check condition list in pair
			if (checkConditionList(capl.list[j].conditionList, event->getSourceId(), sameBeat)) {
				if (capl.list[j].conditionList.hasSound) {
					console->addCommand(commandPlaySound, capl.list[j].conditionList.soundName);
				}
				//if conditions fullfilled or has no conditions execute the actions
				doActionList(&capl.list[j], event->getAmount());
			}
		}
	}
}

float Timer::getPhase() {
	return phase;
}
