#pragma once
#include <vector>
#include <deque>
#include "Sound.h"
#include <glm/glm.hpp>

struct SoundInstance {
	sf::Sound* sfSound;
	bool loops = false;
	bool loopsBetween = false;
	float loopStart = 0;
	float loopEnd = 0;
	std::string soundName;
	int id;
	void loop() {
		loops = true;
		sfSound->setLoop(true);
	}
	void loopBetween(float _start, float _end) {
		loopsBetween = true;
		loopStart = _start;
		loopEnd = _end;
	}
	void stop() {
		sfSound->stop();
	}
	float getPlayingOffset() {
		return sfSound->getPlayingOffset().asSeconds();
	}
	void setVolume(int volume) {
		sfSound->setVolume(volume);
	}
	sf::SoundSource::Status getStatus() {
		return sfSound->getStatus();
	}
	void end() {
		delete sfSound;
	}
	bool getLoopsBetween() {
		return loopsBetween;
	}
	float getLoopEnd() {
		return loopEnd;
	}
	float getLoopStart() {
		return loopStart;
	}
	void setPlayingOffset(float offset) {
		sfSound->setPlayingOffset(sf::seconds(offset));
	}
};

class SoundPlayer {
public:
	SoundPlayer();
	void loadSound(std::string name, std::string path);
	int playSoundByName(std::string name);
	int playSoundByName(std::string name, float volume);
	int playSoundByName(std::string name, float volume, float pitch);
	void loopSound(int id);
	void loopSoundBetween(int id, float start, float end);
	void stopSound(int id);
	float getPlayingOffset(int id);
	void setVolume(int id, float volume);
	float getSpatialVolume(glm::vec2 pos1, glm::vec2 pos2);
	void update();
	void finish();
	void setGlobalVolume(float volume);
	float getGlobalVolume();
private:
	float globalVolume = 1;
	std::vector<Sound*> sounds;
	std::vector<SoundInstance*> soundInstances;
	int nextID = 0;
};