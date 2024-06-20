#include "AutoTurret.h"

AutoTurret::AutoTurret(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, float _x, float _y) :
	Object(_x, _y, 24, 24, 0, immovable, true),
	Living(100, 1, &isLiving),
	PowerNode(_pConsole, 50, 0, &isPowerNode, false, false, 1, _pSpriteCollection, _x, _y, &id)
{
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
	removeFromConnections();
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 10 + rand() % 10);
}

void AutoTurret::update() {
	if (!getBuilt()) setBuilt();
	//if ready to fire, fire (via command)
	if (auto sharedTarget = target.lock()){
		if (getPercentage() > 0) {
			glm::vec2 targetPos = sharedTarget->getCenter();
			glm::vec2 targetVel = glm::vec2(sharedTarget->getBoundingBoxPointer()->xv, sharedTarget->getBoundingBoxPointer()->yv);
			glm::vec2 center = getCenter();
			//get angle from our center to the target and set barrelRotation
			barrelRotation = 180.0f * pConsole->getAtan2Value((targetPos.y - center.y), (targetPos.x - center.x)) / (3.1415);
			if (reloadTimer <= 0) {
				glm::vec2 distVector = targetPos - center;
				float distance = sqrt(distVector.x * distVector.x + distVector.y * distVector.y);
				float timetoTarget = distance / projectileSpeed;
				targetPos += targetVel * timetoTarget;

				pSoundPlayer->playSoundByName("laser_shot2", 0.25 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
				discharge(1);
				if (barrelRotation < 0) {
					barrelRotation += 360; // Adjust for negative angles
				}
				glm::vec2 cosSinValues = pConsole->getTrigValue(barrelRotation);
				shootPos = center + glm::vec2(18 * cosSinValues.x, 18 * cosSinValues.y - 20);
				//glm::vec2 shootPos = center + glm::vec2(18 * cos(3.1415 * barrelRotation / 180.0f), 18 * sin(3.1415 * barrelRotation / 180.0f) - 16);
				float radians = pConsole->getAtan2Value((targetPos.y - shootPos.y), (targetPos.x - shootPos.x));

				pConsole->addCommand(commandAddProjectile, shootPos.x, shootPos.y, radians, projectileSpeed, id, faction);
				reloadTimer = maxReload;
			}
		}
	}
	else {
		hasTarget = false;
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
	discharge(0.2);
	updatePowerPosition(getCenter().x, getCenter().y);
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
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(160, 214, 255), getPercentage() * 2, 3);
	drawPowerConections();
}

void AutoTurret::drawBuilding(){
	baseStack.drawUpTo(boundingBox.x, boundingBox.y, boundingBox.y, rotation, 1);
	baseStack.drawUpToPercent(boundingBox.x, boundingBox.y, boundingBox.y, rotation, buildProgress / 0.3);
	barrelStack.drawUpToPercent(boundingBox.x - 4, boundingBox.y - 16, boundingBox.y + 1, barrelRotation - 90, (buildProgress - 0.3) / 0.7);

	buildHeight = buildProgress * float(15 * 2);
}

void AutoTurret::setTarget(std::shared_ptr<Object> _target) {
	target = _target;
	hasTarget = true;
}

void AutoTurret::RemoveTarget() {
	hasTarget = false;
}

int AutoTurret::getTargetingRange(){
	return targetingRange;
}
