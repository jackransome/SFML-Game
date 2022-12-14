#pragma once
#include <vector>
#include <deque>
#include "Sound.h"
#include <glm/glm.hpp>

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
private:
	std::vector<Sound*> sounds;
	std::vector<sf::Sound*> soundPlayers;
	std::vector<int> soundIDs;
	int nextID = 0;
};