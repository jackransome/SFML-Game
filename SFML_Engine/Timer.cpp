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
		console->addCommand(commandPlaySound, "sh", 0.1);
		//console->addCommand(commandDrawGreenRect);
		console->addCommand(commandAddObject, objectFootprint, 10, 10);
	}
	for (int i = 0; i < events.size(); i++) {
		
		//middle of beat, for doing things and playing sounds
		if (lastPhase < 0.5f && phase >= 0.5f) {
			
			if (events[i]->getBeat() == beat) {
				//run actions
				if (events[i]->getType() == test1) {
					console->addCommand(commandPlaySound, "hh");
					console->addCommand(commandAddObject, objectFootprint, 20, 10);
					//console->addCommand(commandDrawRedRect);
				}
				else if (events[i]->getType() == test2) {
					console->addCommand(commandAddObject, objectFootprint, 20, 10);
					console->addCommand(commandPlaySound, "ohh");
					//console->addCommand(commandDrawRedRect);
				}
				else if (events[i]->getType() == test3) {
					console->addCommand(commandAddObject, objectFootprint, 20, 10);
					console->addCommand(commandPlaySound, "1", events[i]->getAmount());
					//console->addCommand(commandDrawRedRect);
				}
				else if (events[i]->getType() == test4) {
					console->addCommand(commandAddObject, objectFootprint, 20, 10);
					console->addCommand(commandPlaySound, "8tom", events[i]->getAmount(), events[i]->getAmount());
					//console->addCommand(commandDrawRedRect);
				}

			}
		}
		// end of beat, for assessing conditions and adding new events etc
		if (events[i]->getBeat() < beat) {
			//checking if has conditions
			
			int fulfilledCount = 0;
			bool runActions = true;
			CAPairList capl = events[i]->getCAPairs();
			// loop thru pairs
			for (int j = 0; j < capl.size; j++) {
				//loop thru conditions in the pair
				
				//check condition list in pair
				if (checkConditionList(capl.pairs[j]->conditionList, events[i]->getSourceId())) {
					//play sound if there were condition and the pair has a sound
					if (capl.pairs[j]->conditionList.size > 0 && capl.pairs[j]->conditionList.soundName.compare("") != 0) {
						console->addCommand(commandPlaySound, capl.pairs[j]->conditionList.soundName);
					}
					//if conditions fullfilled or has no conditions execture the actions
					doActionList(capl.pairs[j]);
				}
			}
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

void Timer::addEvent(int beatDelay, EventType type, int sourceId, float amount){
	for (int i = 0; i < addedThisBeat.size(); i++) {
		if (addedThisBeat[i] == type) {
			std::cout << "event already added this beat\n";
			return;
		}
	}
	addedThisBeat.push_back(type);

	//if beat delay is 0 then its intended for this beat so ....

	events.push_back(new Event(sourceId, type, amount, beat + beatDelay));
	std::cout << "added event to beat" << beat + beatDelay << "\n";
}

bool Timer::checkConditionList(ConditionList conditionList, int sourceId) {
	bool fulfilled = true;
	bool individualFulfilled;
	for (int k = 0; k < conditionList.size; k++) {
		if (conditionList.list[k]->getLackOf()) {
			individualFulfilled = true;;
		}
		else {
			individualFulfilled = false;
		}

		EventType eType = conditionList.list[k]->getEventType();
		bool sameSourceId = conditionList.list[k]->getSameSourceId();
		for (int l = 0; l < events.size(); l++) {
			//checking if event that happened in the beat just finished matches the condition
			if (events[l]->getBeat() == beat - 1 && events[l]->getType() == eType) {
				//checking for if needs same source id of not, also checking min amount against amount
				if ((sameSourceId || sourceId == events[l]->getSourceId()) && conditionList.list[k]->getMinAmount() <= events[l]->getAmount()) {
					if (conditionList.list[k]->getLackOf()) {
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

bool Timer::doActionList(CAPair* _CAPair) {
	ActionList actionList = _CAPair->actionList;
	for (int k = 0; k < actionList.size; k++) {
		switch (actionList.list[k]->getType()) {
		case a_addEvent:
			addEvent(actionList.list[k]->getEventDelay(), actionList.list[k]->getEventType(), actionList.list[k]->getSourceId(), actionList.list[k]->getAmount() * _CAPair->conditionList.amountModifier);
			console->addCommand(commandAddObject, objectFootprint, 30, 10);
			break;
			/*case a_playSound:
				console->addCommand(commandPlaySound, actionList.list[j]->getSoundName());
				break;*/
		}
	}
}

int Timer::getCurrentTime() {
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
