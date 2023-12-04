#include "Spark.h"

Spark::Spark(SpriteCollection* _pSpriteCollection, glm::vec3 _position, glm::vec3 _velocity, float _brightness, float _colour) :
	Decoration(_pSpriteCollection, position.x, position.y) {
	position = _position;
	velocity = _velocity;
	pSpriteCollection = _pSpriteCollection;
	brightness = _brightness;
	if (_colour == 0) {
		colourVec = glm::vec3(255, 210, 1400);
	}
	else if (_colour == 1) {
		colourVec = glm::vec3(255, 120, 40);
	}
	else if (_colour == 2) {
		colourVec = glm::vec3(200, 200, 255);
	}
	else if (_colour == 3) {
		colourVec = glm::vec3(255, 80, 255);
	}
}

void Spark::update() {
	position += velocity;
	velocity.z -= 0.1;

	if (position.z < 0) {
		position.z = 0;
		velocity.x *= 0.8;
		velocity.y *= 0.8;
	}

	brightness *= 0.93;
	if (brightness < 0.075) {
		toDestroy = true;
	}
}

void Spark::draw(){
	pSpriteCollection->drawLightSource(glm::vec2(position.x, position.y - position.z), colourVec, brightness * ((double)rand() / (RAND_MAX)), 3);
}