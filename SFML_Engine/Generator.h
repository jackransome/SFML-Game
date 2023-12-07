#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "InputManager.h"
#include "Living.h"
#include "Controllable.h"
#include "SoundPlayer.h"
#include "PowerNode.h"

class Generator : public Object, public Living, public PowerNode {
public:
	Generator(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, int x, int y);
	~Generator() override;
	virtual void draw() override;
	virtual void drawBuilding() override;
	virtual void onDeath() override;
	virtual void update() override;
private:
	SpriteStack spriteStack;
	SpriteCollection* pSpriteCollection;
	SoundPlayer* pSoundPlayer;
	int AmbientSoundId;
	int blinkCounter = 0;
	float productionProgress = 0;
	float productionRate;
};