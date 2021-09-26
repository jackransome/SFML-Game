#include "Sound.h"
#include <iostream>
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
