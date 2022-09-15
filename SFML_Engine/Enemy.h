#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "Living.h"

class Enemy : public Object, public Living {
public:
	Enemy(SpriteCollection* _pSpriteCollection, float x, float y);
	virtual void update() override;
	virtual void draw() override;
	void setTarget(int x, int y);
private:
	SpriteCollection* pSpriteCollection;
	float maxVel;
	float acceleration;
	glm::vec2 target;
	glm::vec2 velocity;
	glm::vec2 position;
	void normaliseVec(glm::vec2 *vec);

	SpriteSheet mainAnimation;
};