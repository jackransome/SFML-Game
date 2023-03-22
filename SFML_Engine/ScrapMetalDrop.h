#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "Living.h"

class ScrapMetalDrop : public Object {
public:
	ScrapMetalDrop(SpriteCollection* _pSpriteCollection, int x, int y, b2World* _pPhysicsWorld);
	virtual void draw() override;
	virtual void update() override;
private:
	SpriteStack spriteStack;
	SpriteCollection* pSpriteCollection;
};