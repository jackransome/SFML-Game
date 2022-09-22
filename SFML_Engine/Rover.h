#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "InputManager.h"
#include "Living.h"
#include "Pickuper.h"
#include "SoundPlayer.h"

class Rover : public Object, public Living, public Pickuper {
public:
	Rover(InputManager* _pInputManager, SpriteCollection* pSpriteCollection, SoundPlayer* _pSoundPlayer, float x, float y);
	virtual void update() override;
	virtual void draw() override;
private:
	float direction = 0;
	float speed = 5;
	bool hasCrate = false;
	SoundPlayer* pSoundPlayer;
	SpriteStack spriteStackNormal;
	SpriteStack spriteStackCrate;
	InputManager* pInputManager;
	SpriteCollection* pSpriteCollection;
	int trackTimer = 0;
	int soundId;
	bool soundPlaying = false;
	bool lastHolding;
};