#include "Relay.h"

Relay::Relay(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, int _x, int _y) :
	Object(x, y, 20, 20, 0, immovable, true),
	Living(100, 2, factionFriendly),
	Controllable(500) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	pConsole = _pConsole;
	pSoundPlayer = _pSoundPlayer;
	spriteStack = SpriteStack(pSpriteCollection, "relay_stack_1", 13, 13, 34, 2);
	AmbientSoundId = pSoundPlayer->playSoundByName("relay_ambient_3", 0.1);
	pSoundPlayer->loopSound(AmbientSoundId);
	canBePickedUp = true;
	type = objectRelay;
	isLiving = true;
	buildTime = 8;
}

Relay::~Relay(){
	pSoundPlayer->stopSound(AmbientSoundId);
}

void Relay::draw() {
	float lightPhase = 0.7f+sin(pConsole->getFrame()/80.0f)/2.0f;
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 68), glm::vec3(160, 214, 255), 2* lightPhase, 1);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 68), glm::vec3(160, 214, 255), 0.2* lightPhase, 0);
	spriteStack.draw(boundingBox.x-3, boundingBox.y-3, boundingBox.y-3, rotation);
}

void Relay::drawBuilding(){
	spriteStack.drawUpTo(boundingBox.x - 3, boundingBox.y - 3, boundingBox.y - 3, rotation, 1);
	spriteStack.drawUpToPercent(boundingBox.x - 3, boundingBox.y - 3, boundingBox.y - 3, rotation, buildProgress);

	buildHeight = buildProgress * float(34 * 2);
}

void Relay::onDeath() {
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 15 + rand() % 10);
}

void Relay::update() {
	pSoundPlayer->setVolume(AmbientSoundId, 0.5 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
}
