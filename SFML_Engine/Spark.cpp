#include "Spark.h"

Spark::Spark(SpriteCollection* _pSpriteCollection, glm::vec3 _position, glm::vec3 _velocity, float _brightness) :
	Decoration(_pSpriteCollection, position.x, position.y) {
	position = _position;
	velocity = _velocity;
	pSpriteCollection = _pSpriteCollection;
	brightness = _brightness;
}

void Spark::update() {
	position += velocity;
	velocity.z -= 0.1;

	if (position.z < 0) {
		position.z = 0;
		velocity.x *= 0.8;
		velocity.y *= 0.8;
	}

	brightness *= 0.95;
	if (brightness < 0.05) {
		toDestroy = true;
	}
}

void Spark::draw(){
	pSpriteCollection->drawLightSource(glm::vec2(position.x, position.y - position.z), glm::vec3(255, 210, 1400), brightness * ((double)rand() / (RAND_MAX)), 3);
}