#include "Enemy.h"

Enemy::Enemy(SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, float _x, float _y, b2World* _pPhysicsWorld) :
	Object(_x, _y, 18, 18, 0, movable, true, _pPhysicsWorld),
	Living(100, 1, factionHostile)
{
	position = glm::vec2(_x, _y);
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
	targetingRange = 500;
	AmbientSoundId = pSoundPlayer->playSoundByName("drone_ambient_1", 0.1);
	pSoundPlayer->loopSound(AmbientSoundId);
	pSoundPlayer->setVolume(AmbientSoundId, 0);
	// Create a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((float)_x/100, (float)_y/100);
	physicsBody = pPhysicsWorld->CreateBody(&bodyDef);

	// Attach a shape to the dynamic body
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((boundingBox.w / 2) / 100, (boundingBox.h / 2) / 100);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	physicsBody->CreateFixture(&fixtureDef);

	physicsBodyType = 2;
}

Enemy::~Enemy(){
	pSoundPlayer->stopSound(AmbientSoundId);
}

void Enemy::update() {
	b2Vec2 p = physicsBody->GetPosition();
	boundingBox.x = p.x*100;
	boundingBox.y = p.y*100;

	position.x = boundingBox.x;
	position.y = boundingBox.y;

	if (hasTarget) {
		glm::vec2 newDirection = target - position;
		float distance = sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y);
		if (distance < damageRange && reloadTimer <= 0) {
			


			pConsole->addCommand(commandDoAEODamage, target.x, target.y, 10, 10, id);
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
		normaliseVec(&newDirection);
		velocity = velocity + newDirection * acceleration;
		if (sqrt(velocity.x * velocity.x + velocity.y * velocity.y) > maxVel) {
			normaliseVec(&velocity);
			velocity *= maxVel;
		}
		position = position + velocity;
	}
	else {
		velocity = glm::vec2(0, 0);
	}
	
	reloadTimer--;
	

	

	
	boundingBox.xv = velocity.x;
	boundingBox.yv = velocity.y;
	

	boundingBox.x = boundingBox.x + boundingBox.xv;
	boundingBox.y = boundingBox.y + boundingBox.yv;
	
	physicsBody->SetTransform(b2Vec2(boundingBox.x/100, boundingBox.y/100), 0);
	physicsBody->SetLinearVelocity(b2Vec2(boundingBox.xv/100, boundingBox.yv/100));

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
	pConsole->addCommand(commandPlaySound, "drone_death_2", 0.2);
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x, getCenter().y);
}

void Enemy::setTarget(int x, int y, float xvel, float yvel) {
	target.x = x;
	target.y = y;
	targetVel.x = xvel;
	targetVel.y = yvel;
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
