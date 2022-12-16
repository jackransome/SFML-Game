#include "soundPlayer.h"
#include <iostream>

SoundPlayer::SoundPlayer(){}

void SoundPlayer::loadSound(std::string name, std::string path) {
	sounds.push_back(new Sound(name, path));
}

int SoundPlayer::playSoundByName(std::string name){
	return playSoundByName(name, 1, 1);
}

int SoundPlayer::playSoundByName(std::string name, float volume) {
	return playSoundByName(name, volume, 1);
}

int SoundPlayer::playSoundByName(std::string name, float volume, float pitch) {
	for (int i = 0; i < sounds.size(); i++) {
		if (name.compare(sounds[i]->getName()) == 0) {
			soundInstances.emplace_back(new SoundInstance);
			soundInstances.back()->sfSound = new sf::Sound();
			soundInstances.back()->sfSound->setBuffer(*sounds[i]->getBuffer());
			soundInstances.back()->sfSound->setVolume(volume * 100 * globalVolume);
			soundInstances.back()->sfSound->setPitch(pitch);
			soundInstances.back()->sfSound->play();
			soundInstances.back()->id = nextID;
			nextID++;
			return nextID - 1;
		}
	}
	std::cout << name << " not found\n";
}

void SoundPlayer::loopSound(int id){
	for (int i = 0; i < soundInstances.size(); i++) {
		if (soundInstances[i]->id == id) {
			soundInstances[i]->loop();
		}
	}
}

void SoundPlayer::loopSoundBetween(int id, float start, float end){
	for (int i = 0; i < soundInstances.size(); i++) {
		if (soundInstances[i]->id == id) {
			soundInstances[i]->loopBetween(start, end);
		}
	}
}

void SoundPlayer::stopSound(int id){
	for (int i = 0; i < soundInstances.size(); i++) {
		if (soundInstances[i]->id == id) {
			soundInstances[i]->stop();
			return;
		}
	}
	std::cout << "SOUND ID " << id << " DOES NOT EXIST\n";
}

float SoundPlayer::getPlayingOffset(int id)
{
	for (int i = 0; i < soundInstances.size(); i++) {
		if (soundInstances[i]->id == id) {
			return soundInstances[i]->getPlayingOffset();
		}
	}
	std::cout << "SOUND ID " << id << " DOES NOT EXIST\n";
	return 0;
}

void SoundPlayer::setVolume(int id, float volume){
	for (int i = 0; i < soundInstances.size(); i++) {
		if (soundInstances[i]->id == id) {
			soundInstances[i]->setVolume(volume*100 * globalVolume);
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
	for (int i = 0; i < soundInstances.size(); i++) {
		if (soundInstances[i]->getStatus() == sf::SoundSource::Status::Stopped) {
			soundInstances[i]->end();
			delete soundInstances[i];
			soundInstances.erase(soundInstances.begin() + i);
		}
		else {
			if (soundInstances[i]->getLoopsBetween()) {
				if (soundInstances[i]->getPlayingOffset() > soundInstances[i]->getLoopEnd()) {
					soundInstances[i]->setPlayingOffset(soundInstances[i]->getLoopStart());
				}
			}
		}
	}
}

void SoundPlayer::finish(){
	for (int i = 0; i < soundInstances.size(); i++) {
		soundInstances[i]->stop();
	}
}

void SoundPlayer::setGlobalVolume(float volume){
	globalVolume = volume;
}

float SoundPlayer::getGlobalVolume(){
	return globalVolume;
}
