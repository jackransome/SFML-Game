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
	glm::vec2 perpendicularClockwise(const glm::vec2& v);
	glm::vec2 perpendicularCounterClockwise(const glm::vec2& v);

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
	SpriteSheet animationRunDown;
	SpriteSheet animationRunUp;

	SpriteSheet animationBlinkNa;
	SpriteSheet animationRunLeftNa;
	SpriteSheet animationRunRightNa;
	SpriteSheet animationWalkLeftNa;
	SpriteSheet animationWalkRightNa;
	SpriteSheet animationWalkDownNa;
	SpriteSheet animationWalkUpNa;
	SpriteSheet imageStandBackNa;
	SpriteSheet imageStandLeftNa;
	SpriteSheet imageStandRightNa;
	SpriteSheet animationRunDownNa;
	SpriteSheet animationRunUpNa;

	TextureWrapper* arm;
	TextureWrapper* elbow;

	InputManager* pInputManager;
	SpriteCollection* pSpriteCollection;
	Direction direction;
	glm::vec2 eyePosition1 = glm::vec2(0,0);
	glm::vec2 eyePosition2 = glm::vec2(0, 0);
	glm::vec2 shoulderPos1 = glm::vec2(0, 0);
	glm::vec2 shoulderPos2 = glm::vec2(0, 0);
	glm::vec2 aimCenter = glm::vec2(0, 0);
	glm::vec2 holdPoint = glm::vec2(0, 0);
	glm::vec2 elbow1 = glm::vec2(0, 0);
	glm::vec2 elbow2 = glm::vec2(0, 0);
	glm::vec2 tempV1 = glm::vec2(0, 0);
	glm::vec2 tempV2 = glm::vec2(0, 0);
	float r = 0;
	float tempDistance = 0;
	float tempA = 0;
	float armHalfLength = 10;
	float holdRadius = 11;
	bool eyeVisible1 = false;
	bool eyeVisible2 = false;
	bool usingArms = true;
	float vel;
	bool sprinting;
};