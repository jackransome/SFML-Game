#include "TeleporterPillar.h"

TeleporterPillar::TeleporterPillar(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, int _x, int _y) :
	Object(x, y, 12, 12, 0, immovable, true),
	Living(100, 2, &isLiving),
	PowerNode(_pConsole, 600, 0, &isPowerNode, false, false, 1, _pSpriteCollection, _x, _y, &id)
{
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	pConsole = _pConsole;
	pSoundPlayer = _pSoundPlayer;
	spriteStack = SpriteStack(pSpriteCollection, "teleporter_pillar_stack_1", 7, 7, 18, 2);
	AmbientSoundId = pSoundPlayer->playSoundByName("teleporter_pillar_ambient_1", 0);
	pSoundPlayer->loopSound(AmbientSoundId);
	canBePickedUp = true;
	type = objectTeleporterPillar;
	isLiving = true;
	buildTime = 6;
}

TeleporterPillar::~TeleporterPillar() {
	pSoundPlayer->stopSound(AmbientSoundId);
}

void TeleporterPillar::draw() {
	float lightPhase = 0.7f + sin(pConsole->getFrame() / 10.0f) / 2.0f;
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 68), glm::vec3(255, 50, 255), 2 * lightPhase * getPercentage(), 3);
	spriteStack.draw(boundingBox.x - 1, boundingBox.y - 1, boundingBox.y + boundingBox.h, rotation);
	drawPowerConections();
}

void TeleporterPillar::drawBuilding() {
	spriteStack.drawUpTo(boundingBox.x - 3, boundingBox.y - 3, boundingBox.y - 3, rotation, 1);
	spriteStack.drawUpToPercent(boundingBox.x - 3, boundingBox.y - 3, boundingBox.y - 3, rotation, buildProgress);

	buildHeight = buildProgress * float(18 * 2);
}

void TeleporterPillar::onDeath() {
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 10 + rand() % 5);
}

void TeleporterPillar::update() {
	if (!getBuilt()) setBuilt();
	//pSoundPlayer->setVolume(AmbientSoundId, 0.5 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
	if ((getHealth() / getMaxHealth()) < ((double)rand() / (RAND_MAX)) && ((double)rand() / (RAND_MAX)) > 0.85) {
		if (((double)rand() / (RAND_MAX)) > 0.7) {
			pConsole->addCommand(commandAddObject, objectSpark, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 36 * ((double)rand() / (RAND_MAX)), 1.0);
		}
		else {
			pConsole->addCommand(commandAddObject, objectSmoke, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 36 * ((double)rand() / (RAND_MAX)), 1.0);
		}
	}
	updatePowerPosition(getCenter().x, getCenter().y);
	if (getPercentage() == 1) {
		fullyCharged = true;
	}
}

void TeleporterPillar::setActive(bool _active) {
	active = _active;
}
