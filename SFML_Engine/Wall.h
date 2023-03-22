#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "InputManager.h"

class Wall : public Object {
public:
	Wall(SpriteCollection* pSpriteCollection, int x, int y, int width, int height, b2World* _pPhysicsWorld);
	virtual void draw() override;
private:
	SpriteCollection* pSpriteCollection;
	Image* topImage;
	Image* sideImage;
	Image* edgeImage;
};