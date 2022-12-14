#include "Enemy.h"

Enemy::Enemy(SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, float x, float y) :
	Object(x, y, 18, 18, 0, movable, true),
	Living(100, 1)
{
	position = glm::vec2(x, y);
	target = glm::vec2(0, 0);
	velocity = glm::vec2(0, 0);
	acceleration = 0.6;
	maxVel = 2;
	pSoundPlayer = _pSoundPlayer;
	pSpriteCollection = _pSpriteCollection;
	type = objectEnemy;
	mainAnimation = SpriteSheet(pSpriteCollection, "enemyDrone1", 9, 19, 4, 2);
	mainAnimation.setChangeTimer(3);
	mainAnimation.setOpacity(1);
	hostile = true;
	damageRange = 60;
	maxReload = 15;
	AmbientSoundId = pSoundPlayer->playSoundByName("drone_ambient_1", 0.1);
	pSoundPlayer->loopSound(AmbientSoundId);
}

void Enemy::update() {

	position.x = boundingBox.x;
	position.y = boundingBox.y;



	glm::vec2 newDirection = target - position;
	if (sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y) < damageRange && reloadTimer <= 0) {
		//pConsole->addCommand(commandDoAEODamage, target.x, target.y, 10, 10, id);
		switch (rand() % 5) {
		case 0:
			pConsole->addCommand(commandPlaySound, "drone_zap_1", 0.3 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
			break;
		case 1:
			pConsole->addCommand(commandPlaySound, "drone_zap_2", 0.3 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
			break;
		case 2:
			pConsole->addCommand(commandPlaySound, "drone_zap_3", 0.3 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
			break;
		case 3:
			pConsole->addCommand(commandPlaySound, "drone_zap_4", 0.3 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
			break;
		case 4:
			pConsole->addCommand(commandPlaySound, "drone_zap_5", 0.3 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
			break;
		}
		reloadTimer = maxReload;
	}
	reloadTimer--;
	normaliseVec(&newDirection);

	velocity = velocity + newDirection * acceleration;

	if (sqrt(velocity.x * velocity.x + velocity.y * velocity.y) > maxVel) {
		normaliseVec(&velocity);
		velocity *= maxVel;
	}
	position = position + velocity;
	boundingBox.xv = velocity.x;
	boundingBox.yv = velocity.y;
	//boundingBox.x = position.x;
	//boundingBox.y = position.y;

	boundingBox.x = boundingBox.x + boundingBox.xv;
	boundingBox.y = boundingBox.y + boundingBox.yv;

	//take current velocity, add new direction * accelleration, normalise if magnitude greater than max speed and multiply by max speed
	//velocity = clamp((velocity + (newDirection * acceleration)), max vel)
	pSoundPlayer->setVolume(AmbientSoundId, 0.2*pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
}

void Enemy::draw() {
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x+12, boundingBox.y-12), glm::vec3(255, 0, 0), 2, 1, false);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + 12, boundingBox.y - 12), glm::vec3(255, 0, 0), 0.04, 0, false);
	mainAnimation.run();
	mainAnimation.draw(boundingBox.x, boundingBox.y-18, boundingBox.y + boundingBox.h);
	//pSpriteCollection->addShaderToLast("blur_h");
	//pSpriteCollection->addShaderToLast("blur_v");
	//pSpriteCollection->addShaderToLast("blend");
}

void Enemy::onDeath(){
	pSoundPlayer->stopSound(AmbientSoundId);
	pConsole->addCommand(commandPlaySound, "drone_death_2", 0.2);
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x, getCenter().y);
}

void Enemy::setTarget(int x, int y) {
	target.x = x;
	target.y = y;
}

void Enemy::normaliseVec(glm::vec2* vec) {
	if (!vec->x && !vec->y){
		return;
	}
	float magnitude = sqrt(vec->x*vec->x + vec->y*vec->y);
	vec->x /= magnitude;
	vec->y /= magnitude;
}
