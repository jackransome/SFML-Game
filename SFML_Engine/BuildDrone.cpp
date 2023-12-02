#include "BuildDrone.h"

BuildDrone::BuildDrone(SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, float _x, float _y) :
	Object(_x, _y, 12, 12, 0, droneCol, false)
{
	pSpriteCollection = _pSpriteCollection;
	pSoundPlayer = _pSoundPlayer;
	mainStack = SpriteStack(pSpriteCollection, "build_drone_stack_1", 8, 8, 12, 2);
	type = objectBuildDrone;
}

BuildDrone::~BuildDrone(){
	if (beamSoundPlaying) {
		pSoundPlayer->stopSound(beamSoundId);
	}
}

void BuildDrone::RemoveTarget() {
	hasTarget = false;
}

bool BuildDrone::getHasTarget() {
	return hasTarget;
}

void BuildDrone::update(){
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	if (hasTarget) {
		if (!target->getToBuild() || target->getToDestroy()) {
			hasTarget = false;
			building = false;
		}
		else {
			glm::vec2 targetPos = target->getCenter();
			glm::vec2 center = getCenter();
			glm::vec2 toTarget = targetPos - center;
			distance = sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);
			if (distance < buildRange) {
				building = true;
				target->incrementBuildProgress(0.01);
				if (!beamSoundPlaying) {
					beamSoundId = pSoundPlayer->playSoundByName("build_beam", 0.1 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
					pSoundPlayer->loopSound(beamSoundId);
					beamSoundPlaying = true;
				}
				else {
					pSoundPlayer->setVolume(beamSoundId, 0.1 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
					if (((double)rand() / (RAND_MAX)) < 0.1) {
						pConsole->addCommand(commandAddObject, objectSpark, targetPos.x, targetPos.y, target->getBuildHeight());
					}
				}
				
			}
			else {
				boundingBox.xv = toTarget.x / 12;
				boundingBox.yv = toTarget.y / 12;
				if (beamSoundPlaying) {
					pSoundPlayer->stopSound(beamSoundId);
					beamSoundPlaying = false;
				}
				building = false;
			}
		}
	}
	else {
		if (beamSoundPlaying) {
			pSoundPlayer->stopSound(beamSoundId);
			beamSoundPlaying = false;
		}
		building = false;
	}

	boundingBox.x = boundingBox.x + boundingBox.xv;
	boundingBox.y = boundingBox.y + boundingBox.yv;
	bob_counter += 0.15 * 58;
}

void BuildDrone::draw(){
	float bobHeight = pConsole->getSinValue(bob_counter) * 4;
	if (building) {
		pSpriteCollection->drawBeamLight(getCenter() + glm::vec2(0, bobHeight), target->getCenter() + glm::vec2(0, -target->getBuildHeight()), glm::vec3(200, 200, 255), 0.5, 1);
	}

	

	glm::vec2 cosSinValues = pConsole->getTrigValue(rotation + 135);
	glm::vec2 lightPos = getCenter() + glm::vec2(4 * cosSinValues.x, 4 * cosSinValues.y - 28 + bobHeight);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(160, 214, 255), 2, 2);
	mainStack.draw(boundingBox.x - 2, boundingBox.y - 2 + bobHeight, boundingBox.y, rotation + 90);
}

void BuildDrone::setTarget(Object* _target){
	target = _target;
	hasTarget = true;
	glm::vec2 targetPos = target->getCenter();
	glm::vec2 center = getCenter();
	rotation = 180.0f * atan2((targetPos.y - (center.y - 8 + pConsole->getSinValue(bob_counter) * 4)), (targetPos.x - center.x)) / (3.1415);
}

