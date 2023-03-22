#pragma once
#include "Object.h"
#include "SpriteStack.h"

class Crate : public Object {
public:
	Crate(SpriteCollection* _pSpriteCollection, int x, int y, b2World* _pPhysicsWorld);
	virtual void draw() override;
	virtual void update() override;
private:
	SpriteStack spriteStack;
	SpriteCollection* pSpriteCollection;
};