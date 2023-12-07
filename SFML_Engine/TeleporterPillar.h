#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "InputManager.h"
#include "Living.h"
#include "Controllable.h"
#include "SoundPlayer.h"
#include "PowerNode.h"

class TeleporterPillar : public Object, public Living, public PowerNode {
public:
	TeleporterPillar(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, int x, int y);
	~TeleporterPillar() override;
	virtual void draw() override;
	virtual void drawBuilding() override;
	virtual void onDeath() override;
	virtual void update() override;
	void setActive(bool _active);
private:
	SpriteStack spriteStack;
	SpriteCollection* pSpriteCollection;
	SoundPlayer* pSoundPlayer;
	int AmbientSoundId;
	bool active = false;
};