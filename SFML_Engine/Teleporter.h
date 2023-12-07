#pragma once
#include "Object.h"
#include "SpriteCollection.h"
#include "SoundPlayer.h"

class Teleporter : public Object {
public:
	Teleporter(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, float _x, float _y);
	~Teleporter() override;
	virtual void draw() override;
	virtual void update() override;
private:
	SpriteCollection* pSpriteCollection;
	SoundPlayer* pSoundPlayer;
	int AmbientSoundId;
	int angle = 0;
};