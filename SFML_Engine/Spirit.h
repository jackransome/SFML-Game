#pragma once
#include "Object.h"
#include "Controllable.h"
#include "InputManager.h"
#include "SpriteCollection.h"
#include "SoundPlayer.h"
#include "Living.h";

class Spirit : public Object, public Controllable {
public:
	Spirit(InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, float _x, float _y);
	virtual void update() override;
	virtual void draw() override;
private:
	SoundPlayer* pSoundPlayer;
	SpriteCollection* pSpriteCollection;
	InputManager* pInputManager;
	Console* _pConsole;
};