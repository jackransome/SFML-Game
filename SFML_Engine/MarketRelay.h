#pragma once
#include "Object.h"
#include "Controllable.h"
#include "InputManager.h"
#include "Living.h"
#include "SoundPlayer.h"
#include <algorithm>
#include "SpriteStack.h"

class MarketRelay : public Object, public Living, public Controllable {
public:
	MarketRelay(SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Console* _pConsole, SoundPlayer* _pSoundPlayer, int x, int y);
	~MarketRelay() override;
	virtual void draw() override;
	virtual void onDeath() override;
	virtual void update() override;
	void addCredit(int _credit);
private:
	SpriteCollection* pSpriteCollection;
	SpriteStack spriteStack;
	InputManager* pInputManager;
	Console* pConsole;
	SoundPlayer* pSoundPlayer;
	glm::vec2 startPoint;
	bool startPointValid = false;
	int credits = 0;
	int AmbientSoundId;
	int sellSpaceWidth, sellSpaceHeight;
};