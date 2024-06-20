#include "Spirit.h"


Spirit::Spirit(InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, float _x, float _y) :
	Object(_x, _y, 16, 16, 0, controllable, true),
	Controllable(200, &isControllable) {
	pSpriteCollection = _pSpriteCollection;
	pInputManager = _pInputManager;
	pConsole = _pConsole;
	pSoundPlayer = _pSoundPlayer;
	type = objectDefenseOrb;
	isLiving = true;
	faction = 0;
}

void Spirit::update()
{
}

void Spirit::draw()
{
}
