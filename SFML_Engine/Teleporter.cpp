#include "Teleporter.h"

Teleporter::Teleporter(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, float _x, float _y) :
	Object(_x-15, _y-15, 30, 30, 0, none, false) {
	pConsole = _pConsole;
	pSoundPlayer = _pSoundPlayer;
	pSpriteCollection = _pSpriteCollection;
	AmbientSoundId = pSoundPlayer->playSoundByName("teleporter_ambient_1", 0);
	pSoundPlayer->loopSound(AmbientSoundId);
	type = objectTeleporter;
}

Teleporter::~Teleporter(){
	pSoundPlayer->stopSound(AmbientSoundId);
}

void Teleporter::draw(){
	float orbs = 12;
	glm::vec2 center = getCenter();
	for (int i = 0; i < orbs; i++) {
		pSpriteCollection->drawLightSource(center + 20.0f*glm::vec2(pConsole->getTrigValue(angle + i * (360.0/orbs))), glm::vec3(255, 0, 255), 0.3, 3);
	}
}

void Teleporter::update(){
	pSoundPlayer->setVolume(AmbientSoundId, 0.3 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
	if (((double)rand() / (RAND_MAX)) > 0.8) {
		pConsole->addCommand(commandAddObject, objectSpark, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 0, 3.0);
	}
	angle+=4;
}
