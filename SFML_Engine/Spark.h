#pragma once
#include "Decoration.h"

class Spark : public Decoration {
public:
	Spark(SpriteCollection* _pSpriteCollection, glm::vec3 position, glm::vec3 velocity, float _brightness);
	virtual void draw() override;
	virtual void update() override;
protected:
	glm::vec3 position;
	glm::vec3 velocity;
	float brightness;
	float height;
};