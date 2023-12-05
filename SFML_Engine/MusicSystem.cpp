#include "MusicSystem.h"

MusicSystem::MusicSystem(SoundPlayer* _pSoundPlayer){
	pSoundPlayer = _pSoundPlayer;
}

void MusicSystem::update(){
	long long time = getCurrentTime();
	for (int i = 0; i < playingTracks.size(); i++) {
		if (playingTracks[i].toEnd && playingTracks[i].currentVolume == 0) {
			playingTracks.erase(playingTracks.begin() + i);
			i--;
			continue;
		}
		if (time < playingTracks[i].nextTime) {
			if (time > playingTracks[i].previousTime) {
				float progress = (float(time - playingTracks[i].previousTime) / float(playingTracks[i].nextTime - playingTracks[i].previousTime));
				playingTracks[i].currentVolume = progress * playingTracks[i].nextVolume + (1.0 - progress) * playingTracks[i].previousVolume;
				pSoundPlayer->setVolume(playingTracks[i].id, playingTracks[i].currentVolume);
			}
		}
		else {
			playingTracks[i].currentVolume = playingTracks[i].nextVolume;
			pSoundPlayer->setVolume(playingTracks[i].id, playingTracks[i].currentVolume);
		}
	}
	for (int i = 0; i < delayedPlays.size(); i++) {
		if (time >= delayedPlays[i].startTime) {
			fadeIn(delayedPlays[i].name, delayedPlays[i].duration, delayedPlays[i].volume);
			delayedPlays.erase(delayedPlays.begin() + i);
			i--;
		}
	}
}

void MusicSystem::stopAll(){
	for (int i = 0; i < playingTracks.size(); i++) {
		pSoundPlayer->stopSound(playingTracks[i].id);
	}
	playingTracks.clear();
	delayedPlays.clear();
}

void MusicSystem::fadeIn(std::string name, float duration, float volume){
	int id = pSoundPlayer->playSoundByName(name, 0);
	pSoundPlayer->loopSound(id);
	playingTracks.push_back(PlayingTrack(id, name));
	if (duration == 0) {
		pSoundPlayer->setVolume(id, volume);
	}
	else {
		pSoundPlayer->setVolume(id, 0);
	}
	

	long long time = getCurrentTime();
	playingTracks[playingTracks.size() - 1].currentVolume = 0;
	playingTracks[playingTracks.size() - 1].previousTime = time;
	playingTracks[playingTracks.size() - 1].previousVolume = 0;
	playingTracks[playingTracks.size() - 1].nextTime = time + long(duration * 1000);
	playingTracks[playingTracks.size() - 1].nextVolume = volume;
}

void MusicSystem::fadeInWithDelay(std::string name, float duration, float volume, float delay){
	delayedPlays.push_back(DelayedPlay(name, duration, volume, getCurrentTime() + long(delay * 1000)));
}


void MusicSystem::fadeOut(std::string name, float duration){
	long long time = getCurrentTime();
	for (int i = 0; i < playingTracks.size(); i++) {
		if (playingTracks[i].name == name) {
			playingTracks[i].previousTime = time;
			playingTracks[i].nextTime = time + long(duration * 1000);
			playingTracks[i].previousVolume = playingTracks[i].currentVolume;
			playingTracks[i].nextVolume = 0;
			playingTracks[i].toEnd = true;
			return;
		}
	}
	std::cout << name << " not currently playing\n";
}

void MusicSystem::fadeVolume(std::string name, float amount, float duration){
	long long time = getCurrentTime();
	for (int i = 0; i < playingTracks.size(); i++) {
		if (playingTracks[i].name == name) {
			playingTracks[i].previousTime = time;
			playingTracks[i].nextTime = time + long(duration * 1000);
			playingTracks[i].previousVolume = playingTracks[i].currentVolume;
			playingTracks[i].nextVolume = playingTracks[i].currentVolume + amount;
			return;
		}
	}
	std::cout << name << " not currently playing\n";
}

void MusicSystem::fadeOutAll(float duration){
	delayedPlays.clear();
	long long time = getCurrentTime();
	for (int i = 0; i < playingTracks.size(); i++) {
		playingTracks[i].previousTime = time;
		playingTracks[i].nextTime = time + long(duration * 1000);
		playingTracks[i].previousVolume = playingTracks[i].currentVolume;
		playingTracks[i].nextVolume = 0;
		playingTracks[i].toEnd = true;
	}
}

long long MusicSystem::getCurrentTime()
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::milliseconds milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return milliseconds.count();
}

