#include "EnemyTurretRover.h"

EnemyTurretRover::EnemyTurretRover(SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, float _x, float _y) :
	Object(_x, _y, 18, 18, 0, movable, true),
	Living(100, 1)
{
	target = glm::vec2(0, 0);
	acceleration = 0.6;
	maxVel = 2;
	pSoundPlayer = _pSoundPlayer;
	pSpriteCollection = _pSpriteCollection;
	type = objectEnemyTurretRover;
	baseStack = SpriteStack(pSpriteCollection, "enemy_rover_range_stack_1", 10, 12, 8, 2);
	barrelStack = SpriteStack(pSpriteCollection, "enemy_rover_range_barrel_stack_1", 12, 12, 10, 2);
	baseStack.setRasterizeMode(false);
	hostile = true;
	isLiving = true;
	explodeRange = 60;
	targetingRange = 2000;
	AmbientSoundId = pSoundPlayer->playSoundByName("enemy_turret_rover_ambient_1", 0.1);
	pSoundPlayer->loopSound(AmbientSoundId);
	pSoundPlayer->setVolume(AmbientSoundId, 0);
	isEnemy = true;
	faction = 1;
}

EnemyTurretRover::~EnemyTurretRover() {
	pSoundPlayer->stopSound(AmbientSoundId);
	if (moveSoundPlaying) {
		pSoundPlayer->stopSound(moveSoundId);
	}
}

void EnemyTurretRover::update() {
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	if (hasTarget) {

		glm::vec2 center = getCenter();
		glm::vec2 distV = target - center;
		float distance = sqrt(distV.x * distV.x + distV.y * distV.y);
		if (distance < 20) {
			doDamage(1000000);
		}
		
		if (distance < 500) {
			// shoot at target
			
			glm::vec2 center = getCenter();
			barrelRotation = 180.0f * pConsole->getAtan2Value((target.y - center.y), (target.x - center.x)) / (3.1415);

			if (reloadTimer <= 0) {
				glm::vec2 distVector = pConsole->getControlPosition() - center;
				float distance = sqrt(distVector.x * distVector.x + distVector.y * distVector.y);

				pConsole->addCommand(commandPlaySound, "laser_shot2", 0.25 / (1 + distance / 100));
				if (barrelRotation < 0) {
					barrelRotation += 360; // Adjust for negative angles
				}
				glm::vec2 cosSinValues = pConsole->getTrigValue(barrelRotation);
				glm::vec2 shootPos = center + glm::vec2(18 * cosSinValues.x, 18 * cosSinValues.y - 20);
				//glm::vec2 shootPos = center + glm::vec2(18 * cos(3.1415 * barrelRotation / 180.0f), 18 * sin(3.1415 * barrelRotation / 180.0f) - 16);
				float radians = atan2((target.y - shootPos.y), (target.x - shootPos.x));

				pConsole->addCommand(commandAddProjectile, shootPos.x, shootPos.y, radians, projectileSpeed, id, faction);
				reloadTimer = maxReload;
			}
		}
		else {
			//given current center and target, change current direction
			adjustDirection(center, target, rotation, 0.05);

			// if current direction is within 45 degrees of the right direction, move forwards
			if (isAngleWithinThreshold(center, target, rotation, 3.141592 / 4)) {
				moveTowardsTarget(rotation, speed);
			}
		}
	}
	reloadTimer--;
	//setting volume based on distance
	pSoundPlayer->setVolume(AmbientSoundId, 0.15 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));

	//drawing damage
	if ((getHealth() / getMaxHealth()) < ((double)rand() / (RAND_MAX)) && ((double)rand() / (RAND_MAX)) > 0.85) {
		if (((double)rand() / (RAND_MAX)) > 0.7) {
			pConsole->addCommand(commandAddObject, objectSpark, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 12 * ((double)rand() / (RAND_MAX)), 1.0);
		}
		else {
			pConsole->addCommand(commandAddObject, objectSmoke, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 12 * ((double)rand() / (RAND_MAX)), 1.0);
		}
	}

	if (trackTimer < 19) {
		trackTimer += speed;
	}
	if ((boundingBox.yv != 0 || boundingBox.xv != 0)) {
		if (!moveSoundPlaying) {
			moveSoundId = pSoundPlayer->playSoundByName("enemy_rover_moving", 0.0);
			pSoundPlayer->loopSoundBetween(moveSoundId, 0.3, 1.0);

			moveSoundPlaying = true;
		}
		if (trackTimer >= 19) {
			pConsole->addCommand(commandAddObject, objectRoverTracksMini, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2, (rotation / (2 * 3.1415)) * 360 + 90);
			trackTimer = 0;
		}
	}
	else {
		if (moveSoundPlaying) {
			pSoundPlayer->stopSound(moveSoundId);
			moveSoundPlaying = false;
		}
	}
	if (moveSoundPlaying) {
		pSoundPlayer->setVolume(moveSoundId, 0.15 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
	}
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;

	blinkCounter++;
}

void EnemyTurretRover::draw() {
	baseStack.draw(boundingBox.x + boundingBox.w / 2 - 10, boundingBox.y + boundingBox.h / 2 - 10, boundingBox.y, ((rotation / (2 * 3.1415)) * 360) + 90);

	glm::vec2 cosSinValues = pConsole->getTrigValue(barrelRotation - 161);
	glm::vec2 lightPos = getCenter() + glm::vec2(3.0 * cosSinValues.x + 1, 3.0 * cosSinValues.y - 34);
	if (blinkCounter % 32 > 16) {
		pSpriteCollection->drawLightSource(lightPos, glm::vec3(255, 0, 0), 4, 3);
	}
	else {
		pSpriteCollection->drawLightSource(lightPos, glm::vec3(255, 0, 0), 0.5, 3);
	}
	barrelStack.draw(boundingBox.x - 2, boundingBox.y - 16, boundingBox.y + 1, barrelRotation - 90);
}

void EnemyTurretRover::onDeath() {
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 5 + rand() % 10);
	pConsole->addCommand(commandShakeScreen, 12.5f);
}

void EnemyTurretRover::setTarget(int x, int y) {
	hasTarget = true;
	target.x = x;
	target.y = y;
}

int EnemyTurretRover::getTargetingRange() {
	return targetingRange;
}

void EnemyTurretRover::RemoveTarget() {
	hasTarget = false;
}

void EnemyTurretRover::adjustDirection(const glm::vec2& center, const glm::vec2& target, float& direction, float amount) {
	// Calculate the direction vector from center to target
	glm::vec2 toTarget = target - center;


	// Calculate the current direction vector
	glm::vec2 currentDirection = pConsole->getTrigValue(direction * 180 / 3.151592);

	// Calculate the dot product and the determinant (for cross product in 2D)
	float dot = glm::dot(currentDirection, toTarget);
	float det = currentDirection.x * toTarget.y - currentDirection.y * toTarget.x;

	// Determine the angle difference
	float angleDiff = pConsole->getAtan2Value(det, dot);

	// Adjust the direction
	if (1 > 0) {
		direction += std::min(angleDiff, amount); // Adjust by a small step, e.g., 0.1 radian
	}
	else if (1 < 0) {
		direction += std::max(angleDiff, -amount); // Adjust by a small step, e.g., -0.1 radian
	}
	// Normalize the direction to keep it in the range [0, 2 * PI)
	//direction = 1;// std::fmod(direction + 2 * 3.141592, 2 * 3.141592);
	direction = direction - floor(direction / (2 * 3.141592)) * (2 * 3.141592);
}

void EnemyTurretRover::moveTowardsTarget(float& direction, float amount) {

	// Create a movement vector in the adjusted direction
	glm::vec2 cosSinValues = pConsole->getTrigValue(direction * 180 / 3.151592);
	glm::vec2 movementVector(cosSinValues.x, cosSinValues.y);

	// Move the center towards the target
	glm::vec2 movement = movementVector * amount;
	boundingBox.xv = movement.x;
	boundingBox.yv = movement.y;
}

float EnemyTurretRover::normalizeAngle(float angle) {
	return std::fmod(angle + 2 * 3.141592, 2 * 3.141592);
}

bool EnemyTurretRover::isAngleWithinThreshold(const glm::vec2& point1, const glm::vec2& point2, float angle, float threshold) {
	// Calculate the vector from point1 to point2
	glm::vec2 vectorToPoint2 = point2 - point1;

	// Calculate the true angle from point1 to point2
	float trueAngle = pConsole->getAtan2Value(vectorToPoint2.y, vectorToPoint2.x);

	// Normalize the angles
	trueAngle = normalizeAngle(trueAngle);
	angle = normalizeAngle(angle);

	// Calculate the difference in angles, considering the circular nature of angles
	float angleDiff = std::abs(trueAngle - angle);
	angleDiff = std::min(angleDiff, static_cast<float>(2 * 3.141592) - angleDiff);

	// Check if the angle difference is within the threshold
	return angleDiff <= threshold;
}