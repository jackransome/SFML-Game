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
		//beat++;
		//console->addCommand(commandPlaySound, "hh", 20);
		console->addCommand(commandDrawGreenRect);
	}
	for (int i = 0; i < events.size(); i++) {
		
		//middle of beat, for doing things and playing sounds
		if (lastPhase < 0.5f && phase >= 0.5f) {
			if (i == 0) {
				std::cout << beat << "MIDDLE\n";
				std::cout << events[i]->getBeat() << "\n";
				std::cout << beat << "\n";
			}
			if (events[i]->getBeat() == beat) {
				//run actions
				if (events[i]->getType() == test1) {
					console->addCommand(commandPlaySound, "hh");
					console->addCommand(commandDrawRedRect);
				}
				else if (events[i]->getType() == test2) {
					console->addCommand(commandPlaySound, "ohh");
					console->addCommand(commandDrawRedRect);
				}

			}
		}
		// end of beat, for assessing conditions etc
		if (events[i]->getBeat() < beat) {
			//checking if has conditions
			bool fulfilled = true;
			if (events[i]->getHasConditions()) {
				// if condition met, do actions / add events
				ConditionList condList = events[i]->getConditions();
				for (int j = 0; j < condList.size; j++) {
					EventType eType = condList.list[i].getEventType();
					for (int k = 0; k < events.size(); k++) {
						//checking if event that happened in the beat just finished matches the condition
						if (events[k]->getBeat() == beat - 1 && events[k]->getType() == eType) {
							//checking for if needs same source id of not
							if (!condList.list[j].getSameSourceId() || events[i]->getSourceId() == events[k]->getSourceId()) {

							} else {
								fulfilled = false;
							}
						} else {
							fulfilled = false;
						}
					}
					if (!fulfilled) {
						break;
					}
				}
			}
			if (fulfilled) {
				//if conditions fullfilled or has no conditions execture the actions
				ActionList actionList = events[i]->getActions();
				for (int j = 0; j < actionList.size; j++) {
					switch (actionList.list[j].getEventType()) {
						//ADD HERE NEXT
					}
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
}

void Timer::changeBpm(int _bpm) {
	bpm = _bpm;
	msInOneBeat = 60000 / bpm;
}

void Timer::addEvent(int beatDelay, EventType type, int sourceId, float amount){
	events.push_back(new Event(sourceId, type, amount, beat + beatDelay));
	std::cout << "added event to beat" << beat + beatDelay << "\n";
}

int Timer::getCurrentTime() {
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
