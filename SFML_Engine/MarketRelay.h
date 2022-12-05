#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "Controllable.h"
#include "InputManager.h"

class MarketRelay : public Object, public Controllable {
public:
	MarketRelay(SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Console* _pConsole, int x, int y);
	virtual void draw() override;
	virtual void update() override;
	void addCredit(int _credit);
private:
	SpriteCollection* pSpriteCollection;
	SpriteSheet spriteSheet;
	InputManager* pInputManager;
	Console* pConsole;
	glm::vec2 startPoint;
	bool startPointValid = false;
	int credits = 0;
};