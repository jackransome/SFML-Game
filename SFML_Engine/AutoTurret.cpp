#include "AutoTurret.h"

AutoTurret::AutoTurret(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, float _x, float _y) :
	Object(_x, _y, 24, 24, 0, immovable, true),
	Living(100, 1, &isLiving)
{
	target = glm::vec2(0, 0);
	pSpriteCollection = _pSpriteCollection;
	pConsole = _pConsole;
	type = objectAutoTurret;
	pSoundPlayer = _pSoundPlayer;
	baseStack = SpriteStack(pSpriteCollection, "autoturret_base_stack", 12, 12, 4, 2);
	barrelStack = SpriteStack(pSpriteCollection, "autoturret_barrel_stack", 16, 16, 11, 2);
	targetingRange = 600;
	canBePickedUp = true;
	maxReload = 15;
	isLiving = true;
	buildTime = 3;
	faction = 0;
}
void AutoTurret::onDeath() {
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 10 + rand() % 10);
}

void AutoTurret::update() {
	//get angle from our center to the target and set barrelRotation
	
	//std::cout << target.x << "|" << target.y << "|" << barrelRotation << "\n";
	//if ready to fire, fire (via command)
	if (hasTarget ){
		
		glm::vec2 center = getCenter();
		barrelRotation = 180.0f * pConsole->getAtan2Value((target.y - center.y), (target.x - center.x)) / (3.1415);
		if (reloadTimer <= 0) {
			glm::vec2 distVector = target - center;
			float distance = sqrt(distVector.x * distVector.x + distVector.y * distVector.y);
			float timetoTarget = distance / projectileSpeed;
			target += targetVel * timetoTarget;


			//pConsole->addCommand(commandPlaySound, "laser_shot2", 0.25 / (1 + distance / 100));
			if (barrelRotation < 0) {
				barrelRotation += 360; // Adjust for negative angles
			}
			glm::vec2 cosSinValues = pConsole->getTrigValue(barrelRotation);
			shootPos = center + glm::vec2(18 * cosSinValues.x, 18 * cosSinValues.y - 20);
			//glm::vec2 shootPos = center + glm::vec2(18 * cos(3.1415 * barrelRotation / 180.0f), 18 * sin(3.1415 * barrelRotation / 180.0f) - 16);
			float radians = pConsole->getAtan2Value((target.y - shootPos.y), (target.x - shootPos.x));

			pConsole->addCommand(commandAddProjectile, shootPos.x, shootPos.y, radians, projectileSpeed, id, faction);
			reloadTimer = maxReload;
		}
	}
	reloadTimer--;
	if ((getHealth() / getMaxHealth()) < ((double)rand() / (RAND_MAX)) && ((double)rand() / (RAND_MAX)) > 0.85) {
		if (((double)rand() / (RAND_MAX)) > 0.7) {
			pConsole->addCommand(commandAddObject, objectSpark, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 5.0, 1.0);
		}
		else {
			pConsole->addCommand(commandAddObject, objectSmoke, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 1.0, 1.0);
		}
	}
}

void AutoTurret::draw() {
	if (barrelRotation < 0) {
		barrelRotation += 360; // Adjust for negative angles
	}
	glm::vec2 cosSinValues = pConsole->getTrigValue(barrelRotation - 144);
	//glm::vec2 lightPos = getCenter() + glm::vec2(1 * cosSinValues.x -1 * cosSinValues.y, 1 * cosSinValues.y + 1 * cosSinValues.x - 34);

	//21, 23
	glm::vec2 lightPos = getCenter() + glm::vec2(8.6 * cosSinValues.x, 8.6 * cosSinValues.y + 7 - 42);

	baseStack.draw(boundingBox.x, boundingBox.y, boundingBox.y, rotation);
	barrelStack.draw(boundingBox.x - 4, boundingBox.y - 16, boundingBox.y + 1, barrelRotation - 90);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(160, 214, 255), 2, 3);
}

void AutoTurret::drawBuilding(){
	baseStack.drawUpTo(boundingBox.x, boundingBox.y, boundingBox.y, rotation, 1);
	baseStack.drawUpToPercent(boundingBox.x, boundingBox.y, boundingBox.y, rotation, buildProgress / 0.3);
	barrelStack.drawUpToPercent(boundingBox.x - 4, boundingBox.y - 16, boundingBox.y + 1, barrelRotation - 90, (buildProgress - 0.3) / 0.7);

	buildHeight = buildProgress * float(15 * 2);
}

void AutoTurret::setTarget(int x, int y, float xvel, float yvel) {
	target.x = x;
	target.y = y;
	targetVel.x = xvel;
	targetVel.y = yvel;
	hasTarget = true;
}

void AutoTurret::RemoveTarget() {
	hasTarget = false;
}

int AutoTurret::getTargetingRange(){
	return targetingRange;
}
