#pragma once
#include "ObjectCollection.h"
#include "SoundPlayer.h"
#include "Camera.h"
#include "SpriteCollection.h"

class CommandExecuter {
public:
	CommandExecuter();
	CommandExecuter(ObjectCollection* _pObjectCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera, SpriteCollection* _pSpriteCollection);
	void execute(Command command);
private:
	ObjectCollection* pObjectCollection;
	SoundPlayer* pSoundPlayer;
	Camera* pCamera;
	SpriteCollection* pSpriteCollection;
};