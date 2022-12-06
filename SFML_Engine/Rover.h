#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "InputManager.h"
#include "Living.h"
#include "Pickuper.h"
#include "SoundPlayer.h"
#include "Controllable.h"
#include "Miner.h"

class Rover : public Object, public Living, public Pickuper, public Controllable, public Miner {
public:
	Rover(InputManager* _pInputManager, SpriteCollection* pSpriteCollection, SoundPlayer* _pSoundPlayer, float x, float y);
	virtual void update() override;
	virtual void draw() override;
private:
	float direction = 0;
	float speed = 0;
	float maxSpeed = 5;
	bool hasCrate = false;
	SoundPlayer* pSoundPlayer;
	SpriteStack spriteStackNormal;
	SpriteStack spriteStackRelay;
	SpriteStack spriteStackCrate;
	InputManager* pInputManager;
	SpriteCollection* pSpriteCollection;
	int trackTimer = 0;
	int moveSoundId;
	int mineSoundId;
	bool moveSoundPlaying = false;
	bool mineSoundPlaying = false;
	bool lastHolding;
};