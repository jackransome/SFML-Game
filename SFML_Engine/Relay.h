#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "InputManager.h"
#include "Living.h"

class Relay : public Object, public Living {
public:
	Relay(SpriteCollection* _pSpriteCollection, int x, int y);
	virtual void draw() override;
private:
	SpriteStack spriteStack;
	SpriteCollection* pSpriteCollection;
};