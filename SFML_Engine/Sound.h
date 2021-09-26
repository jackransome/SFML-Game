#pragma once
#include <SFML/Audio.hpp>

class Sound {
public:
	Sound();
	Sound(std::string name, std::string path);
	sf::SoundBuffer* getBuffer();
	std::string getName();
private:
	sf::SoundBuffer buffer;
	std::string name;
};