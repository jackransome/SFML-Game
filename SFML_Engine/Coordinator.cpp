#include "Coordinator.h"

Coordinator::Coordinator(MusicSystem* _pMusicSystem, Console* _pConsole, SnowSystem* _snowSystem){
	pMusicSystem = _pMusicSystem;
	pConsole = _pConsole;
	snowSystem = _snowSystem;
}

void Coordinator::update(int generatorCount, glm::vec2 generatorPos){

	if (generatorCount && !lastGenertorCount) {
		pConsole->addCommand(commandPlaySound, "distant_roar", 1.0);
		pMusicSystem->fadeInWithDelay("music_ominous_1", 1, 0.35, 2);
		pMusicSystem->fadeOut("475", 1);
		pMusicSystem->fadeInWithDelay("music_beat_1", 0, 0.7, 4);
		snowSystem->changeSpeed(6);
		snowSystem->changeFallAngle(0.5);
		snowSystem->changeSize(150);
		snowSystem->changeOpacity(0.7);
		snowSystem->setSinMultiplier(2);
	}
	else if (!generatorCount && lastGenertorCount) {
		pMusicSystem->fadeOut("music_ominous_1", 3);
		pMusicSystem->fadeIn("475", 5, 0.5);
		pMusicSystem->fadeOut("music_beat_1", 3);
		snowSystem->changeSpeed(2.5);
		snowSystem->changeFallAngle(1.5);
		snowSystem->changeSize(50);
		snowSystem->changeOpacity(0.6);
		snowSystem->setSinMultiplier(2);
	}

	if (generatorCount) {
		//spawn enemies

		if (((float)rand() / (float)RAND_MAX) > 0.975) {
			int distance = 1000 + ((float)rand() / (float)RAND_MAX) * 500;
			float angle = ((float)rand() / (float)RAND_MAX) * 360;
			glm::vec2 location = generatorPos + pConsole->getTrigValue(angle) * float(distance);

			if (((float)rand() / (float)RAND_MAX) < 0.8) {
				pConsole->addCommand(commandAddObject, objectEnemy, location.x, location.y);
			}
			else {
				pConsole->addCommand(commandAddObject, objectEnemyBombRover, location.x, location.y);
			}
			


		}


		

	}

	lastGenertorCount = generatorCount;
}
