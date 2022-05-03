#include "soundPlayer.h"
#include <iostream>

SoundPlayer::SoundPlayer(){}

void SoundPlayer::loadSound(std::string name, std::string path) {
	sounds.push_back(new Sound(name, path));
}

void SoundPlayer::playSoundByName(std::string name){
	for (int i = 0; i < sounds.size(); i++) {
		if (name.compare(sounds[i]->getName()) == 0) {
			soundPlayers.emplace_back(sf::Sound());
			soundPlayers.back().setBuffer(*sounds[i]->getBuffer());
			soundPlayers.back().play();
			return;
		}
	}
	std::cout << name << " not found\n";
}

void SoundPlayer::playSoundByName(std::string name, float volume) {
	for (int i = 0; i < sounds.size(); i++) {
		if (name.compare(sounds[i]->getName()) == 0) {
			soundPlayers.emplace_back(sf::Sound());
			soundPlayers.back().setBuffer(*sounds[i]->getBuffer());
			soundPlayers.back().setVolume(volume * 100);
			soundPlayers.back().play();
			return;
		}
	}
	std::cout << name << " not found\n";
}

void SoundPlayer::update() {
	if (soundPlayers.size() > 0) {
		std::cout << soundPlayers.front().getStatus() << "\n";
	}
	
	if (soundPlayers.size() > 0 && soundPlayers.front().getStatus() == sf::SoundSource::Status::Stopped) {
		
		soundPlayers.pop_front();;
	}
}
