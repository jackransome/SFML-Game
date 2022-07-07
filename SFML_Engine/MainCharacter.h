#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "InputManager.h"
#include "Living.h"

enum Direction {up, down, left, right};

class MainCharacter : public Object, public Living {
public:
	MainCharacter(InputManager* _pInputManager, SpriteCollection* pSpriteCollection, float x, float y);
	virtual void update() override;
	virtual void draw() override;
private:
	int blinkCounter = 0;
	SpriteSheet animationBlink;
	SpriteSheet animationRunLeft;
	SpriteSheet animationRunRight;
	SpriteSheet animationWalkLeft;
	SpriteSheet animationWalkRight;
	SpriteSheet animationWalkDown;
	SpriteSheet animationWalkUp;
	SpriteSheet imageStandBack;
	SpriteSheet imageStandLeft;
	SpriteSheet imageStandRight;
	SpriteSheet miniAnimation;
	SpriteSheet animationRunDown;
	InputManager* pInputManager;
	SpriteCollection* pSpriteCollection;
	Direction direction;
	float vel;
	bool sprinting;
};