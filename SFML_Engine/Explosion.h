#pragma once
#include "Decoration.h"
#include "SoundPlayer.h"

class Explosion : public Decoration {
public:
	Explosion(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* pSoundPlayer, float x, float y, float size);
	virtual void draw() override;
	virtual void update() override;
protected:
	float timer;
	float size;
	SoundPlayer* pSoundPlayer;
	Console* pConsole;
};