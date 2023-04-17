#pragma once
#include "Object.h"
#include "Controllable.h"
#include "InputManager.h"
#include "Living.h"
#include "SoundPlayer.h"
#include <algorithm>
#include "SpriteStack.h"

class Jammer : public Object, public Living {
public:
	Jammer(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, int x, int y, b2World* _pPhysicsWorld);
	~Jammer();
	virtual void draw() override;
	virtual void update() override;
	virtual void onDeath() override;
private:
	SpriteCollection* pSpriteCollection;
	SpriteStack spriteStack;
	Console* pConsole;
	SoundPlayer* pSoundPlayer;
	int AmbientSoundId;
};