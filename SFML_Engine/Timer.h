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
	void addEvent(int beatDelay, EventType type, int sourceId, float amount, bool accuracy);
	bool checkConditionList(ConditionList conditionList, int sourceId, bool sameBeat);
	void doActionList(CAPair* _CAPair);
	void runPairs(Event* event, bool post, bool sameBeat);
private:
	int getCurrentTime();
	int bpm; //beats per minute
	float phase; // between 0 and 1, current phase in the beat
	float lastPhase;
	int beat; //what beat is currently up to
	int startTime; //start time
	int now; //curent time in ms
	int msInOneBeat;
	std::vector<Event*> events;
	std::vector<EventType> addedThisBeat;
	Console* console;
};