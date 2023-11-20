#include "Projectile.h"

Projectile::Projectile(SpriteCollection* _pSpriteCollection, float _x, float _y, float _rotation, float _speed, int _fromID){
	position = glm::vec2(_x, _y);
	pSpriteCollection = _pSpriteCollection;
	rotation = _rotation;
	speed = _speed;
	velocity = glm::vec2(speed * cos(rotation), speed * sin(rotation));
	lastPosition = position;
	fromID = _fromID;
}

void Projectile::run(){
	lastPosition = position;
	position += velocity;
	distanceTraveled += speed;
	if (distanceTraveled > range) {
		toDelete = true;
	}
}

void Projectile::pull(float _force, glm::vec2 _position){
	glm::vec2 differenceVector = _position - position;
	float distance = sqrt(differenceVector.x * differenceVector.x + differenceVector.y * differenceVector.y);
	differenceVector /= distance;
	velocity += differenceVector * _force;
}

void Projectile::draw(){
	pSpriteCollection->drawBeamLight(lastPosition, position, glm::vec3(255, 150, 100), 0.075, 0);
	pSpriteCollection->drawBeamLight(lastPosition, position, glm::vec3(255, 150, 100), 0.5, 0.5);
	//pSpriteCollection->drawBeamLight(lastPosition, position, glm::vec3(255, 150, 100), 10, 1.5);
	
}

void Projectile::setPosition(glm::vec2 _position){
	position = _position;
}

int Projectile::getFromID(){
	return fromID;
}
