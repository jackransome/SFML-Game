#include "Generator.h"

Generator::Generator(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, int _x, int _y) :
	Object(x, y, 34, 34, 0, immovable, true),
	Living(100, 2, &isLiving),
	PowerNode(_pConsole, 100, 0, &isPowerNode, true, true, 5, _pSpriteCollection, _x, _y, &id) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	pConsole = _pConsole;
	pSoundPlayer = _pSoundPlayer;
	spriteStack = SpriteStack(pSpriteCollection, "generator_stack_2", 18, 18, 20, 2);
	AmbientSoundId = pSoundPlayer->playSoundByName("generator_ambient_1", 0.4);
	pSoundPlayer->loopSound(AmbientSoundId);
	pSoundPlayer->setVolume(AmbientSoundId, 0);
	canBePickedUp = true;
	type = objectGenerator;
	isLiving = true;
	buildTime = 8;
	productionRate = 0.004;
	faction = 0;
}

Generator::~Generator() {
	pSoundPlayer->stopSound(AmbientSoundId);
	removeFromConnections();
}

void Generator::update() {
	if (!getBuilt()) setBuilt();
	pSoundPlayer->setVolume(AmbientSoundId, 0.5 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
	glm::vec2 smokePos = getCenter() + glm::vec2(0, + 25);
	pConsole->addCommand(commandAddObject, objectSmoke, smokePos.x, smokePos.y, 60.0, 1.5);
	blinkCounter++;

	productionProgress += productionRate;
	if (productionProgress >= 1.0) {
		pConsole->addCommand(commandAddToInventory, Resource::component, 1);
		productionProgress = 0;
		glm::vec2 distVector = pConsole->getControlPosition() - getCenter();
		float distance = sqrt(distVector.x * distVector.x + distVector.y * distVector.y);

		pConsole->addCommand(commandPlaySound, "generator_produce_1", 0.25 / (1 + distance / 100));
	}
	if ((getHealth() / getMaxHealth()) < ((double)rand() / (RAND_MAX)) && ((double)rand() / (RAND_MAX)) > 0.85) {
		if (((double)rand() / (RAND_MAX)) > 0.7) {
			pConsole->addCommand(commandAddObject, objectSpark, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 40 * ((double)rand() / (RAND_MAX)), 1.0);
		}
		else {
			pConsole->addCommand(commandAddObject, objectSmoke, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 40 * ((double)rand() / (RAND_MAX)), 1.0);
		}
	}
	addCharge(1);
}


void Generator::draw() {
	
	spriteStack.draw(boundingBox.x - 2, boundingBox.y - 2, boundingBox.y + boundingBox.h, rotation);


	float intensity = 1.5;
	if (blinkCounter % 8 > 3) {
		intensity = 0.3;
	}
	glm::vec2 center = getCenter();
	glm::vec2 cosSinValues = pConsole->getTrigValue(rotation);
	glm::vec2 lightPos = center + glm::vec2(17 * cosSinValues.x - 17 * cosSinValues.y, 17 * cosSinValues.y + 17 * cosSinValues.x - 25);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(80, 255, 90), intensity, 3);

	lightPos = center - glm::vec2(17 * cosSinValues.x - 17 * cosSinValues.y, 17 * cosSinValues.y + 17 * cosSinValues.x + 25);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(80, 255, 90), intensity, 3);

	lightPos = center + glm::vec2(17 * cosSinValues.x + 17 * cosSinValues.y, 17 * cosSinValues.y - 17 * cosSinValues.x - 25);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(80, 255, 90), intensity, 3);

	lightPos = center - glm::vec2(17 * cosSinValues.x + 17 * cosSinValues.y, 17 * cosSinValues.y - 17 * cosSinValues.x + 25);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(80, 255, 90), intensity, 3);

	//glm::vec2 lightPos = center + glm::vec2(17 * cosSinValues.x - 17 * cosSinValues.y, 17 * cosSinValues.y + 17 * cosSinValues.x - 25);
	//pSpriteCollection->drawLightSource(lightPos, glm::vec3(100, 255, 120), 2, 2);
	//glm::vec2 lightPos = center + 
	drawConections();
	updatePosition(getCenter().x, getCenter().y);
}

void Generator::drawBuilding() {
	spriteStack.drawUpTo(boundingBox.x - 2, boundingBox.y - 2, boundingBox.y - 2, rotation, 1);
	spriteStack.drawUpToPercent(boundingBox.x - 2, boundingBox.y - 2, boundingBox.y - 2, rotation, buildProgress);

	buildHeight = buildProgress * float(22 * 2);


}

void Generator::onDeath() {
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 15 + rand() % 10);
}