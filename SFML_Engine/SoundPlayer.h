#pragma once
#include <vector>
#include "Sound.h"

class SoundPlayer {
public:
	SoundPlayer();
	void loadSound(std::string name, std::string path);
	void playSoundByName(std::string name);

private:
	sf::Sound sound;
	std::vector<Sound*> sounds;
};