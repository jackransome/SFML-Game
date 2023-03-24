#include "Sound.h"
#include <iostream>
#include <juce_audio_basics/juce_audio_basics.h>

Sound::Sound() {}

Sound::Sound(std::string _name, std::string path){
	name = _name;
	buffer = sf::SoundBuffer();
	if (!buffer.loadFromFile(path)) {
		std::cout << "failed to load " << path << "\n";
	}
}

sf::SoundBuffer* Sound::getBuffer() {
	return &buffer;
}

std::string Sound::getName() {
	return name;
}

bool Sound::getLoopsBetween(){
	return loopsBetween;
}

void Sound::setLoopsBetween(float start, float end){
	loopsBetween = true;
	loopStart = start;
	loopEnd = end;
}

float Sound::getLoopStart(){
	return loopStart;
}

float Sound::getLoopEnd() {
	return loopEnd;
}
