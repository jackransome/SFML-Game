#include "Enemy.h"

Enemy::Enemy(SpriteCollection* _pSpriteCollection, float x, float y) :
	Object(x, y, 18, 18, 0, movable, true),
	Living(100, 1)
{
	position = glm::vec2(x, y);
	target = glm::vec2(0, 0);
	velocity = glm::vec2(0, 0);
	acceleration = 0.6;
	maxVel = 2;

	pSpriteCollection = _pSpriteCollection;
	type = 2;
	mainAnimation = SpriteSheet(pSpriteCollection, "enemyDrone1", 9, 19, 4, 2);
	mainAnimation.setChangeTimer(3);
	mainAnimation.setOpacity(1);
}

void Enemy::update() {

	position.x = boundingBox.x;
	position.y = boundingBox.y;

	boundingBox.x = boundingBox.x + boundingBox.xv;
	boundingBox.y = boundingBox.y + boundingBox.yv;

	glm::vec2 newDirection;
	newDirection = target - position;
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



	//take current velocity, add new direction * accelleration, normalise if magnitude greater than max speed and multiply by max speed
	//velocity = clamp((velocity + (newDirection * acceleration)), max vel)
}

void Enemy::draw() {
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x+12, boundingBox.y-12), glm::vec3(255, 0, 0), 2, 1, false);
	mainAnimation.run();
	mainAnimation.draw(boundingBox.x, boundingBox.y-18, boundingBox.y + boundingBox.h);
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
