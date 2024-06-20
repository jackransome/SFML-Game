#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "InputManager.h"
#include "Living.h"
#include "Controllable.h"
#include "PowerNode.h"

enum Direction {up, down, left, right};

class MainCharacter : public Object, public Living, public Controllable, public PowerNode {
public:
	MainCharacter(InputManager* _pInputManager, SpriteCollection* pSpriteCollection, Console* _pConsole, float x, float y);
	virtual void update() override;
	virtual void onDeath() override;
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
	SpriteSheet animationRunUp;
	InputManager* pInputManager;
	SpriteCollection* pSpriteCollection;
	Direction direction;
	glm::vec2 eyePosition1 = glm::vec2(0,0);
	glm::vec2 eyePosition2 = glm::vec2(0, 0);
	bool eyeVisible1 = false;
	bool eyeVisible2 = false;
	float vel;
	bool sprinting;
};