#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "InputManager.h"
#include "Living.h"

class Rover : public Object, public Living {
public:
	Rover(InputManager* _pInputManager, SpriteCollection* pSpriteCollection, float x, float y);
	virtual void update() override;
	virtual void draw() override;
private:
	float direction = 0;
	float speed = 5;
	bool hasCrate = false;
	SpriteStack spriteStackNormal;
	SpriteStack spriteStackCrate;
	InputManager* pInputManager;
	SpriteCollection* pSpriteCollection;
};