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
	std::cout << lastPhase << "\n";
	std::cout << phase << "\n";
	if (lastPhase < 0.5f && phase >= 0.5f) {
		std::cout << "here\n";
		beat++;
		console->addCommand(commandPlaySound, "hh", 20);
		console->addCommand(commandDrawGreenRect);
	}
	for (int i = 0; i < events.size(); i++) {
		if (events[i]->getBeat() == beat && phase >= events[i]->getPhase()) {
			if (events[i]->getHasConditions()) {
				//if condition not met, delete and continue


			}
			//run actions
			if (events[i]->getType() == test1) {
				console->addCommand(commandPlaySound, "hh");
				console->addCommand(commandDrawRedRect);
			}
			else if (events[i]->getType() == test2) {
				console->addCommand(commandPlaySound, "ohh");
				console->addCommand(commandDrawRedRect);
			}
			//delete
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
	events.push_back(new Event(sourceId, type, amount, beat + beatDelay, phase));
}

int Timer::getCurrentTime() {
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
