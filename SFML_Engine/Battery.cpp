#include "Battery.h"

Battery::Battery(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, int _x, int _y) :
	Object(x, y, 14, 14, 0, immovable, true),
	Living(100, 2, &isLiving),
	PowerNode(_pConsole, 80, 80, &isPowerNode, true, false, 0.1, _pSpriteCollection, _x, _y, &id) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	pConsole = _pConsole;
	pSoundPlayer = _pSoundPlayer;
	spriteStack = SpriteStack(pSpriteCollection, "battery_stack", 10, 10, 20, 2);
	AmbientSoundId = pSoundPlayer->playSoundByName("sound_battery", 0);
	pSoundPlayer->loopSound(AmbientSoundId);
	canBePickedUp = true;
	type = objectBattery;
	isLiving = true;
	buildTime = 8;
	faction = 0;
}

Battery::~Battery() {
	pSoundPlayer->stopSound(AmbientSoundId);
	removeFromConnections();
}

void Battery::draw() {
	float lightPhase = 0.5f + sin(pConsole->getFrame() / 50.0f) / 3.0f; // 160, 214, 255
	glm::vec3 colour = glm::vec3(255, 80, 255);
	if (active) {
		colour = glm::vec3(255, 0, 230);
		lightPhase = 1;
	}
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 40), glm::vec3(20, 255, 20), getPercentage() * 2, 3);
	//pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 68), glm::vec3(255, 100, 255), 0.2* lightPhase, 0);
	spriteStack.draw(boundingBox.x - 3, boundingBox.y - 3, boundingBox.y + boundingBox.h, rotation);
	drawPowerConections();
}

void Battery::drawBuilding() {
	spriteStack.drawUpTo(boundingBox.x - 3, boundingBox.y - 3, boundingBox.y - 3, rotation, 1);
	spriteStack.drawUpToPercent(boundingBox.x - 3, boundingBox.y - 3, boundingBox.y - 3, rotation, buildProgress);

	buildHeight = buildProgress * float(20 * 2);
}

void Battery::onDeath() {
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 15 + rand() % 10);
}

void Battery::update() {
	if (!getBuilt()) setBuilt();
	pSoundPlayer->setVolume(AmbientSoundId, getPercentage() * 0.10 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
	if ((getHealth() / getMaxHealth()) < ((double)rand() / (RAND_MAX)) && ((double)rand() / (RAND_MAX)) > 0.85) {
		if (((double)rand() / (RAND_MAX)) > 0.7) {
			pConsole->addCommand(commandAddObject, objectSpark, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 60 * ((double)rand() / (RAND_MAX)), 1.0);
		}
		else {
			pConsole->addCommand(commandAddObject, objectSmoke, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 60 * ((double)rand() / (RAND_MAX)), 1.0);
		}
	}
	updatePowerPosition(getCenter().x, getCenter().y);
}

void Battery::setActive(bool _active) {
	active = _active;
}
