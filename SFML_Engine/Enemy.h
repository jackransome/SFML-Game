#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "Living.h"

class Enemy : public Object, public Living {
public:
	Enemy(SpriteCollection* _pSpriteCollection, float x, float y);
	virtual void update() override;
	virtual void draw() override;
private:
	SpriteCollection* pSpriteCollection;
	float vel;
};