#include "EnemyBombRover.h"

EnemyBombRover::EnemyBombRover(SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, float _x, float _y) :
	Object(_x, _y, 18, 18, 0, movable, true),
	Living(100, 1)
{
	target = glm::vec2(0, 0);
	acceleration = 0.6;
	maxVel = 2;
	pSoundPlayer = _pSoundPlayer;
	pSpriteCollection = _pSpriteCollection;
	type = objectEnemyBombRover;
	stack = SpriteStack(pSpriteCollection, "enemy_rover_bomb_stack_1", 10, 12, 8, 2); //CHANGE
	stack.setRasterizeMode(false);
	hostile = true;
	isLiving = true;
	explodeRange = 60;
	targetingRange = 1000;
	AmbientSoundId = pSoundPlayer->playSoundByName("enemy_bomb_1", 0.1);
	pSoundPlayer->loopSound(AmbientSoundId);
	pSoundPlayer->setVolume(AmbientSoundId, 0);
	isEnemy = true;
	faction = 1;
}

EnemyBombRover::~EnemyBombRover(){
	pSoundPlayer->stopSound(AmbientSoundId);
}

void EnemyBombRover::update(){
	if (hasTarget) {
		
		glm::vec2 center = getCenter();
		glm::vec2 distV = target - center;
		float distance = sqrt(distV.x * distV.x + distV.y * distV.y);
		if (distance < 20) {
			doDamage(1000000);
		}

		//given current center and target, change current direction
		adjustDirection(center, target, rotation, 0.05);
		
		// if current direction is within 45 degrees of the right direction, move forwards
		if (isAngleWithinThreshold(center, target, rotation, 3.141592 / 4)) {
			moveTowardsTarget(rotation, 2);
		}
	}
	pSoundPlayer->setVolume(AmbientSoundId, 0.15 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
	if ((getHealth() / getMaxHealth()) < ((double)rand() / (RAND_MAX)) && ((double)rand() / (RAND_MAX)) > 0.85) {
		if (((double)rand() / (RAND_MAX)) > 0.7) {
			pConsole->addCommand(commandAddObject, objectSpark, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 12 * ((double)rand() / (RAND_MAX)), 1.0);
		}
		else {
			pConsole->addCommand(commandAddObject, objectSmoke, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 12 * ((double)rand() / (RAND_MAX)), 1.0);
		}
	}
}

void EnemyBombRover::draw(){
	stack.draw(boundingBox.x + boundingBox.w / 2 - 10, boundingBox.y + boundingBox.h / 2 - 10, boundingBox.y, ((rotation / (2 * 3.1415)) * 360)+90);
	pSpriteCollection->drawLightSource(getCenter() + glm::vec2(0, -17), glm::vec3(255, 0, 0), 2, 3);
}

void EnemyBombRover::onDeath(){
	pConsole->addCommand(commandDoAEODamage, getCenter().x, getCenter().y, 30, 30, id);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 10 + rand() % 10);
	pConsole->addCommand(commandShakeScreen, 20.0f);
}

void EnemyBombRover::setTarget(int x, int y){
	hasTarget = true;
	target.x = x;
	target.y = y;
}

int EnemyBombRover::getTargetingRange(){
	return targetingRange;
}

void EnemyBombRover::RemoveTarget(){
	hasTarget = false;
}

void EnemyBombRover::adjustDirection(const glm::vec2& center, const glm::vec2& target, float& direction, float amount) {
	// Calculate the direction vector from center to target
	glm::vec2 toTarget = target - center;


	// Calculate the current direction vector
	glm::vec2 currentDirection = pConsole->getTrigValue(direction * 180 / 3.151592);

	// Calculate the dot product and the determinant (for cross product in 2D)
	float dot = glm::dot(currentDirection, toTarget);
	float det = currentDirection.x* toTarget.y - currentDirection.y * toTarget.x;

	// Determine the angle difference
	float angleDiff =  pConsole->getAtan2Value(det, dot);

	// Adjust the direction
	if (1 > 0) {
		direction +=  std::min(angleDiff, amount); // Adjust by a small step, e.g., 0.1 radian
	}
	else if (1 < 0) {
		direction += std::max(angleDiff, -amount); // Adjust by a small step, e.g., -0.1 radian
	}
	// Normalize the direction to keep it in the range [0, 2 * PI)
	//direction = 1;// std::fmod(direction + 2 * 3.141592, 2 * 3.141592);
	direction = direction - floor(direction / (2 * 3.141592)) * (2 * 3.141592);
}

void EnemyBombRover::moveTowardsTarget(float& direction, float amount) {

	// Create a movement vector in the adjusted direction
	glm::vec2 cosSinValues = pConsole->getTrigValue(direction * 180 / 3.151592);
	glm::vec2 movementVector(cosSinValues.x, cosSinValues.y);

	// Move the center towards the target
	glm::vec2 movement = movementVector * amount;
	boundingBox.x += movement.x;
	boundingBox.y += movement.y;
}

float EnemyBombRover::normalizeAngle(float angle) {
	return std::fmod(angle + 2 * 3.141592, 2 * 3.141592);
}

bool EnemyBombRover::isAngleWithinThreshold(const glm::vec2& point1, const glm::vec2& point2, float angle, float threshold) {
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