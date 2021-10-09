#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "InputManager.h"

class MainCharacter : public Object {
public:
	MainCharacter(InputManager* _pInputManager, SpriteCollection* pSpriteCollection, float x, float y);
	virtual void update() override;
	virtual void draw() override;
private:
	SpriteSheet animation1;
	InputManager* pInputManager;
	SpriteCollection* pSpriteCollection;
};