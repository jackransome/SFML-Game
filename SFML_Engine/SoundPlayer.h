#pragma once
#include <vector>
#include <deque>
#include "Sound.h"

class SoundPlayer {
public:
	SoundPlayer();
	void loadSound(std::string name, std::string path);
	void playSoundByName(std::string name);
	void playSoundByName(std::string name, float volume);
	void update();
private:
	std::vector<Sound*> sounds;
	std::deque<sf::Sound> soundPlayers;
};