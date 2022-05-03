#include "Timer.h"

Timer::Timer(int _bpm, Console* _console){
	changeBpm(_bpm);
	console = _console;
	beat = 0;
	phase = 0;
}

void Timer::update(){
	phase += timeVel;
	if (phase >= 1.0f) {
		phase -= 1.0f;
		beat++;
		console->addCommand(commandPlaySound, "hh", 20);
	}
	for (int i = 0; i < events.size(); i++) {
		if (events[i]->getBeat() == beat && phase >= events[i]->getPhase()) {
			if (events[i]->getHasConditions()) {
				//if condition not met, delete and continue


			}
			//run actions
			if (events[i]->getType() == test1) {
				console->addCommand(commandPlaySound, "hh");
			}
			else if (events[i]->getType() == test2) {
				console->addCommand(commandPlaySound, "ohh");
			}
			//delete
			events.erase(events.begin() + i);
			i--;

		}
	}
}

void Timer::changeBpm(int _bpm) {
	bpm = _bpm;
	timeVel = (float)bpm / (60.0f * 60.0f);
}

void Timer::addEvent(int beatDelay, EventType type, int sourceId, float amount){
	events.push_back(new Event(sourceId, type, amount, beat + beatDelay, phase));
}
