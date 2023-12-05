#pragma once

#include "MusicSystem.h"
#include "Console.h"
#include "SnowSystem.h"

class Coordinator {
public:
	Coordinator(){};
	Coordinator(MusicSystem* _pMusicSystem, Console* _pConsole, SnowSystem* _snowSystem);
	void update(int generatorCount, glm::vec2 generatorPos);
private:
	int lastGenertorCount = 0;
	MusicSystem* pMusicSystem;
	Console* pConsole;
	SnowSystem* snowSystem;
};