#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "InputManager.h"
#include "Living.h"
#include "Controllable.h"
#include "SoundPlayer.h"
#include "PowerNode.h"

class Relay : public Object, public Living, public PowerNode {
public:
	Relay(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, int x, int y);
	~Relay() override;
	virtual void draw() override;
	virtual void drawBuilding() override;
	virtual void onDeath() override;
	virtual void update() override;
	void setActive(bool _active);
private:
	bool active = false;
	SpriteStack spriteStack;
	SpriteCollection* pSpriteCollection;
	SoundPlayer* pSoundPlayer;
	int AmbientSoundId;
};