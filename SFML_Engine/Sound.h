#pragma once
#include <SFML/Audio.hpp>

class Sound {
public:
	Sound();
	Sound(std::string name, std::string path);
	sf::SoundBuffer* getBuffer();
	std::string getName();
	bool getLoopsBetween();
	void setLoopsBetween(float start, float end);
	float getLoopStart();
	float getLoopEnd();
private:
	sf::SoundBuffer buffer;
	std::string name;
	bool loopsBetween = false;
	float loopStart;
	float loopEnd;

};