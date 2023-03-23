#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "Controllable.h"
#include "InputManager.h"
#include "Living.h"
#include "SoundPlayer.h"
#include <algorithm>

class MarketRelay : public Object, public Living, public Controllable {
public:
	MarketRelay(SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Console* _pConsole, SoundPlayer* _pSoundPlayer, int x, int y, b2World* _pPhysicsWorld);
	virtual void draw() override;
	virtual void update() override;
	virtual void onDeath() override;
	void addCredit(int _credit);
private:
	SpriteCollection* pSpriteCollection;
	SpriteSheet spriteSheet;
	InputManager* pInputManager;
	Console* pConsole;
	SoundPlayer* pSoundPlayer;
	glm::vec2 startPoint;
	bool startPointValid = false;
	int credits = 0;
	int AmbientSoundId;
	int sellSpaceWidth, sellSpaceHeight;
	TextureWrapper* selectionBox;
};