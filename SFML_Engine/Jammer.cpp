#include "Jammer.h"

Jammer::Jammer(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, int _x, int _y) :
	Object(_x, _y, 16, 16, 0, immovable, true),
	Living(100, 2) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	pConsole = _pConsole;
	pSoundPlayer = _pSoundPlayer;
	spriteStack = SpriteStack(pSpriteCollection, "jammer_stack_1", 8, 8, 16, 2);
	canBePickedUp = true;
	type = objectJammer;
	isLiving = true;
	AmbientSoundId = pSoundPlayer->playSoundByName("jammer_ambient_1", 0.1);
	pSoundPlayer->loopSound(AmbientSoundId);
	faction = 0;
}

Jammer::~Jammer() {
	pSoundPlayer->stopSound(AmbientSoundId);
}

void Jammer::draw(){
	spriteStack.draw(boundingBox.x, boundingBox.y, boundingBox.y, rotation);
	//spriteSheet.draw(boundingBox.x, boundingBox.y-30, boundingBox.y);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + 8, boundingBox.y + 8 - 32), glm::vec3(160, 214, 255), 2, 1);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + 8, boundingBox.y + 8 - 32), glm::vec3(160, 214, 255), 0.2, 0);
}

void Jammer::update(){
	pSoundPlayer->setVolume(AmbientSoundId, 0.05 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
}

void Jammer::onDeath(){
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x, getCenter().y);
}
