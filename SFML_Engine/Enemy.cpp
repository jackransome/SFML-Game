#include "Enemy.h"

Enemy::Enemy(SpriteCollection* _pSpriteCollection, float x, float y) :
	Object(x, y, 30, 30, 0, movable, true),
	Living(100, 1)
{
	pSpriteCollection = _pSpriteCollection;
}

void Enemy::update() {
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}

void Enemy::draw() {
	pSpriteCollection->addRectDraw(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, 0, sf::Color(255, 255, 0));
}
