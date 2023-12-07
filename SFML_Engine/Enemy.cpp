#include "Enemy.h"

Enemy::Enemy(SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, float _x, float _y) :
	Object(_x, _y, 18, 18, 0, controllable, true),
	Living(100, 1, &isLiving)
{
	acceleration = 0.6;
	maxVel = 2;
	pSoundPlayer = _pSoundPlayer;
	pSpriteCollection = _pSpriteCollection;
	type = objectEnemy;
	mainAnimation = SpriteSheet(pSpriteCollection, "enemyDrone1", 9, 19, 4, 2);
	mainAnimation.setChangeTimer(3);
	mainAnimation.setOpacity(1);
	hostile = true;
	isLiving = true;
	damageRange = 60;
	maxReload = 15;
	targetingRange = 2000;
	AmbientSoundId = pSoundPlayer->playSoundByName("drone_ambient_1", 0.1);
	pSoundPlayer->loopSound(AmbientSoundId);
	pSoundPlayer->setVolume(AmbientSoundId, 0);
	isEnemy = true;
	faction = 1;
}

Enemy::~Enemy(){
	pSoundPlayer->stopSound(AmbientSoundId);
}

void Enemy::update() {
	boundingBox.xv = 0;
	boundingBox.yv = 0;

	if (auto sharedTarget = target.lock()) {
		glm::vec2 targetPos = sharedTarget->getCenter();
		glm::vec2 newDirection = targetPos - getCenter();
		float distance = sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y);
		if (distance < damageRange && reloadTimer <= 0) {

			pConsole->addCommand(commandDoAEODamage, targetPos.x, targetPos.y, 10, 10, id);
			switch (rand() % 4) {
			case 0:
				pConsole->addCommand(commandPlaySound, "drone_hit_1", 0.3 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
				break;
			case 1:
				pConsole->addCommand(commandPlaySound, "drone_hit_2", 0.3 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
				break;
			case 2:
				pConsole->addCommand(commandPlaySound, "drone_hit_3", 0.3 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
				break;
			case 3:
				pConsole->addCommand(commandPlaySound, "drone_hit_4", 0.3 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
				break;
			}
			pConsole->addCommand(commandShakeScreen, 2.0f);
			reloadTimer = maxReload;
		}
		else {
			normaliseVec(&newDirection);
			boundingBox.xv = newDirection.x * maxVel;
			boundingBox.yv = newDirection.y * maxVel;
		}
	}
	else {
		hasTarget = false;
	}
	
	reloadTimer--;
	

	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
	

	//take current velocity, add new direction * accelleration, normalise if magnitude greater than max speed and multiply by max speed
	//velocity = clamp((velocity + (newDirection * acceleration)), max vel)
	pSoundPlayer->setVolume(AmbientSoundId, 0.15*pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
	
	if ((getHealth() / getMaxHealth()) < ((double)rand() / (RAND_MAX)) && ((double)rand() / (RAND_MAX)) > 0.85) {
		if (((double)rand() / (RAND_MAX)) > 0.7) {
			pConsole->addCommand(commandAddObject, objectSpark, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 5.0, 1.0);
		}
		else {
			pConsole->addCommand(commandAddObject, objectSmoke, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 1.0, 1.0);
		}
	}
}

void Enemy::draw() {
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x+12, boundingBox.y + 6), glm::vec3(255, 0, 0), 2, 3);
	
	mainAnimation.run();
	mainAnimation.draw(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h);
	//pSpriteCollection->addShaderToLast("blur_h");
	//pSpriteCollection->addShaderToLast("blur_v");
	//pSpriteCollection->addShaderToLast("blend");
}

void Enemy::onDeath(){
	//pConsole->addCommand(commandPlaySound, "drone_death_2", 0.3 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 5 + rand()%10);
	pConsole->addCommand(commandShakeScreen, 12.5f);
}

void Enemy::setTarget(std::shared_ptr<Object> _target) {
	target = _target;
	hasTarget = true;
}

int Enemy::getTargetingRange(){
	return targetingRange;
}

void Enemy::RemoveTarget(){
	hasTarget = false;
}

void Enemy::normaliseVec(glm::vec2* vec) {
	if (!vec->x && !vec->y){
		return;
	}
	float magnitude = sqrt(vec->x*vec->x + vec->y*vec->y);
	vec->x /= magnitude;
	vec->y /= magnitude;
}
