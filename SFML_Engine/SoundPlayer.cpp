#include "soundPlayer.h"
#include <iostream>

SoundPlayer::SoundPlayer(){
	sound = sf::Sound();
}

void SoundPlayer::loadSound(std::string name, std::string path) {
	sounds.push_back(new Sound(name, path));
}

void SoundPlayer::playSoundByName(std::string name){
	for (int i = 0; i < sounds.size(); i++) {
		if (name.compare(sounds[i]->getName()) == 0) {
			sound.setBuffer(*sounds[i]->getBuffer());
			sound.play();
		}
		else {
			std::cout << name << " not found\n";
		}
	}
}
