#include "soundPlayer.h"
#include <iostream>

SoundPlayer::SoundPlayer(){}

void SoundPlayer::loadSound(std::string name, std::string path) {
	sounds.push_back(new Sound(name, path));
}

int SoundPlayer::playSoundByName(std::string name){
	for (int i = 0; i < sounds.size(); i++) {
		if (name.compare(sounds[i]->getName()) == 0) {
			soundPlayers.emplace_back(new sf::Sound());
			soundIDs.emplace_back(nextID);
			nextID++;
			soundPlayers.back()->setBuffer(*sounds[i]->getBuffer());
			soundPlayers.back()->play();
			return nextID - 1;
		}
	}
	std::cout << name << " not found\n";
}

int SoundPlayer::playSoundByName(std::string name, float volume) {
	for (int i = 0; i < sounds.size(); i++) {
		if (name.compare(sounds[i]->getName()) == 0) {
			soundPlayers.emplace_back(new sf::Sound());
			soundIDs.emplace_back(nextID);
			nextID++;
			soundPlayers.back()->setBuffer(*sounds[i]->getBuffer());
			soundPlayers.back()->setVolume(volume * 100);
			soundPlayers.back()->play();
			return nextID - 1;
		}
	}
	std::cout << name << " not found\n";
}

int SoundPlayer::playSoundByName(std::string name, float volume, float pitch) {
	for (int i = 0; i < sounds.size(); i++) {
		if (name.compare(sounds[i]->getName()) == 0) {
			soundPlayers.push_back(new sf::Sound());
			soundIDs.push_back(nextID);
			nextID++;
			soundPlayers[soundPlayers.size() - 1]->setBuffer(*sounds[i]->getBuffer());
			soundPlayers[soundPlayers.size() - 1]->setVolume(volume * 100);
			soundPlayers[soundPlayers.size() - 1]->setPitch(pitch);
			soundPlayers[soundPlayers.size() - 1]->play();
			return nextID - 1;
		}
	}
	std::cout << name << " not found\n";
}

void SoundPlayer::loopSound(int id){
	for (int i = 0; i < soundPlayers.size(); i++) {
		if (soundIDs[i] == id) {
			soundPlayers[i]->setLoop(true);
		}
	}
}

void SoundPlayer::loopSoundBetween(int id, float start, float end){
	for (int i = 0; i < soundPlayers.size(); i++) {
		if (soundIDs[i] == id) {
			sounds[i]->setLoopsBetween(start, end);
		}
	}
}

void SoundPlayer::stopSound(int id){
	for (int i = 0; i < soundPlayers.size(); i++) {
		if (soundIDs[i] == id) {
			soundPlayers[i]->stop();
			return;
		}
	}
	std::cout << "SOUND ID " << id << " DOES NOT EXIST\n";
}

float SoundPlayer::getPlayingOffset(int id)
{
	for (int i = 0; i < soundPlayers.size(); i++) {
		if (soundIDs[i] == id) {
			return soundPlayers[i]->getPlayingOffset().asSeconds();
		}
	}
	std::cout << "SOUND ID " << id << " DOES NOT EXIST\n";
	return 0;
}

void SoundPlayer::setVolume(int id, float volume){
	for (int i = 0; i < soundPlayers.size(); i++) {
		if (soundIDs[i] == id) {
			//soundPlayers[i]->pause();
			soundPlayers[i]->setVolume(volume*100);
			//soundPlayers[i]->play();
			return;
		}
	}
	std::cout << "SOUND ID " << id << " DOES NOT EXIST\n";
}

float SoundPlayer::getSpatialVolume(glm::vec2 pos1, glm::vec2 pos2)
{
	return 1 / (1 + pow(sqrt(pow(pos1.x-pos2.x,2)+ pow(pos1.y - pos2.y, 2)) / 200, 2));
}

void SoundPlayer::update() {
	for (int i = 0; i < soundPlayers.size(); i++) {
		if (soundPlayers[i]->getStatus() == sf::SoundSource::Status::Stopped) {
			delete soundPlayers[i];
			soundPlayers.erase(soundPlayers.begin() + i);
			soundIDs.erase(soundIDs.begin() + i);
		}
		else {
			if (sounds[i]->getLoopsBetween()) {
				if (soundPlayers[i]->getPlayingOffset().asSeconds() > sounds[i]->getLoopEnd()) {
					soundPlayers[i]->setPlayingOffset(sf::seconds( sounds[i]->getLoopStart()));
				}
			}
		}
	}
}


void SoundPlayer::finish(){
	for (int i = 0; i < soundPlayers.size(); i++) {
		soundPlayers[i]->stop();
	}
}
