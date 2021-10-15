#pragma once
#include "ObjectCollection.h"
#include "SoundPlayer.h"
#include "Camera.h"

class CommandExecuter {
public:
	CommandExecuter();
	CommandExecuter(ObjectCollection* _pObjectCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera);
	void execute(Command command);
private:
	ObjectCollection* pObjectCollection;
	SoundPlayer* pSoundPlayer;
	Camera* pCamera;
};