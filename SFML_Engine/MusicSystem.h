#pragma once
#include "SoundPlayer.h"
#include <chrono>

struct PlayingTrack {
	PlayingTrack(int _id, std::string _name) {
		id = _id;
		name = _name;
	}
	int id;
	std::string name;
	float previousVolume = 0;
	float nextVolume = 0;
	long long previousTime = 0;
	long long nextTime = 0;
	float currentVolume = 0;
	bool toEnd = false;
};

struct DelayedPlay {
	DelayedPlay(std::string _name, float _duration, float _volume, long long _startTime) {
		name = _name;
		duration = _duration;
		volume = _volume;
		startTime = _startTime;
	}
	std::string name;
	float duration;
	float volume;
	long long startTime;
};

class MusicSystem {
public:
	MusicSystem(){};
	MusicSystem(SoundPlayer* _pSoundPlayer);
	void update();
	void stopAll();
	void fadeIn(std::string name, float duration, float volume);
	void fadeInWithDelay(std::string name, float duration, float volume, float delay);
	void fadeOut(std::string name, float duration);
	void fadeVolume(std::string name, float amount, float duration);
	void fadeOutAll(float duration);
private:
	long long getCurrentTime();
	SoundPlayer* pSoundPlayer;
	std::vector<PlayingTrack> playingTracks;
	std::vector<DelayedPlay> delayedPlays;
};