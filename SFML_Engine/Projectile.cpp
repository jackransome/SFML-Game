#include "Projectile.h"

Projectile::Projectile(SpriteCollection* _pSpriteCollection, Console* _pConsole, float _x, float _y, float _rotation, float _speed, int _fromID, int _faction) {
	position = glm::vec2(_x, _y);
	pSpriteCollection = _pSpriteCollection;
	rotation = _rotation;
	speed = _speed;
	velocity = glm::vec2(speed * cos(rotation), speed * sin(rotation));
	lastPosition = position;
	faction = _faction;
	pConsole = _pConsole;
	fromID = _fromID;
}

void Projectile::run(){
	lastPosition = position;
	position += velocity;
	distanceTraveled += speed;
	if (distanceTraveled > range) {
		toDelete = true;
		glm::vec2 distVector = pConsole->getControlPosition() - position;
		float distance = sqrt(distVector.x * distVector.x + distVector.y * distVector.y);
		pConsole->addCommand(commandPlaySound, "laser_impact", 0.2 / (1 + distance / 100));
		pConsole->addCommand(commandAddObject, objectSmoke, position.x, position.y, 0.0, 1.0);
		pConsole->addCommand(commandAddObject, objectSpark, position.x, position.y, 0.0, 1.0);
	}
}

void Projectile::pull(float _force, glm::vec2 _position){
	glm::vec2 differenceVector = _position - position;
	float distance = sqrt(differenceVector.x * differenceVector.x + differenceVector.y * differenceVector.y);
	differenceVector /= distance;
	velocity += differenceVector * _force;
}

void Projectile::draw(){
	//pSpriteCollection->drawBeamLight(lastPosition, position, glm::vec3(255, 150, 100), 0.075, 0);
	pSpriteCollection->drawBeamLight(lastPosition, position, glm::vec3(255, 150, 100), 0.75, 2);
}

void Projectile::setPosition(glm::vec2 _position){
	position = _position;
}

int Projectile::getFaction(){
	return faction;
}

int Projectile::getFromID()
{
	return fromID;
}
