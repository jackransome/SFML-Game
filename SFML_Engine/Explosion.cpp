#include "Explosion.h"
#include <algorithm>

Explosion::Explosion(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, float x, float y, float _size) :
	Decoration(_pSpriteCollection, x, y) {
	type = objectExplosion;
	timer = _size;
	size = _size;
	pConsole = _pConsole;
	
	pSoundPlayer = pSoundPlayer;
	int temp = size*2 + rand() % 3;
	for (int i = 0; i < temp; i++) {
		pConsole->addCommand(commandAddObject, objectSmoke, getCenter().x + 2 * (-(size*2.5) / 2 + rand() % (int)(size*2.5)), getCenter().y + 2 * (-(size * 2.5) / 2 + rand() % (int)(size * 2.5)), 0.0, 3.0f);
		if (i % 3 == 0) {
			pConsole->addCommand(commandAddObject, objectSpark, x + size * ((double)rand() / (RAND_MAX)), y + size * ((double)rand() / (RAND_MAX)), 5.0, 1.0);
		}
	}
	pConsole->addCommand(commandAddObject, objectSmoke, getCenter().x, getCenter().y, 0.0, 3.0f);
	pConsole->addCommand(commandShakeScreen, (size/5)*12.5f);
	pConsole->addCommand(commandPlaySound, "explosion" + std::to_string(rand() % 3 + 1), size/4 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
	
	
	
}

void Explosion::draw()
{
	int g = rand() % 170;
	int b = (rand() % 2) ? (rand()%20) : (abs(g - (rand() % 20)));
	pSpriteCollection->drawLightSource(getCenter() + glm::vec2(rand()%(int)size, rand() % (int)size), glm::vec3(255, g, b), (timer/5.0)*(0.05 + 0.25*((float)(rand()%10)/10.0)), 0);
	if (timer > size - 0.5) {
		pSpriteCollection->drawLightSource(getCenter() + glm::vec2(rand() % (int)size, rand() % (int)size), glm::vec3(255, 230, 180), size / 10, 0);
	}
	if (timer > size - 2.5) {
		int temp = std::max(1.0f,size - 4 + rand() % 2);
		for (int i = 0; i < temp; i++) {
			pSpriteCollection->drawLightSource(getCenter() + glm::vec2(rand() % (int)(size*2), rand() % (int)(size*2)), glm::vec3(255, 230, 180), size*2 + size*(rand()%3), 1);
		}
	}
}

void Explosion::update()
{
	timer -= 0.5;
	if (timer < 0) {
		toDestroy = true;
	}
}
