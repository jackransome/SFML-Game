#pragma once
#include "Console.h"
#include "Event.h"
#include <vector>

class Timer {
public:
	Timer(){}
	Timer(int _bpm, Console* _console);
	void update();
	void changeBpm(int _bpm);
	void addEvent(int beatDelay, EventType type, int sourceId, float amount);
private:
	int bpm;
	float timeVel;
	float phase;
	int beat;
	std::vector<Event*> events;
	Console* console;
};