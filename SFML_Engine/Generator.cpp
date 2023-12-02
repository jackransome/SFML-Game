#include "Generator.h"

Generator::Generator(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, int _x, int _y) :
	Object(x, y, 36, 28, 0, immovable, true),
	Living(100, 2, factionFriendly),
	Controllable(500) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	pConsole = _pConsole;
	pSoundPlayer = _pSoundPlayer;
	spriteStack = SpriteStack(pSpriteCollection, "generator_stack_1", 20, 16, 20, 2);
	AmbientSoundId = pSoundPlayer->playSoundByName("generator_ambient_1", 0.4);
	pSoundPlayer->loopSound(AmbientSoundId);
	canBePickedUp = true;
	type = objectRelay;
	isLiving = true;
	buildTime = 8;
}

Generator::~Generator() {
	pSoundPlayer->stopSound(AmbientSoundId);
}

void Generator::draw() {
	glm::vec2 lightPos = getCenter() + glm::vec2(5 * cos(direction) - 11 * sin(direction), 5 * sin(direction) + 11 * cos(direction) - 26);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(160, 214, 255), 2, 2);
	glm::vec2 lightPos = getCenter() + glm::vec2(5 * cos(direction) - 11 * sin(direction), 5 * sin(direction) + 11 * cos(direction) - 26);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(160, 214, 255), 2, 2);
	spriteStack.draw(boundingBox.x - 2, boundingBox.y - 2, boundingBox.y - 2, rotation);
}

void Generator::drawBuilding() {
	spriteStack.drawUpTo(boundingBox.x - 3, boundingBox.y - 3, boundingBox.y - 3, rotation, 1);
	spriteStack.drawUpToPercent(boundingBox.x - 3, boundingBox.y - 3, boundingBox.y - 3, rotation, buildProgress);

	buildHeight = buildProgress * float(40 * 2);
}

void Generator::onDeath() {
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 15 + rand() % 10);
}

void Generator::update() {
	pSoundPlayer->setVolume(AmbientSoundId, 0.5 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
}
