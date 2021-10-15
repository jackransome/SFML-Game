#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "InputManager.h"

class Wall : public Object {
public:
	Wall(SpriteCollection* pSpriteCollection, int x, int y, int width, int height);
	virtual void draw() override;
private:
	SpriteCollection* pSpriteCollection;
};