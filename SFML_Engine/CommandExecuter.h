#pragma once
#include "ObjectCollection.h"
#include "SoundPlayer.h"
#include "Camera.h"
#include "SpriteCollection.h"
#include "InputManager.h"
#include "UIManager.h"

class CommandExecuter {
public:
	CommandExecuter();
	CommandExecuter(ObjectCollection* _pObjectCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera, SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, UIManager* _pUIManager);
	void execute(Command command);
private:
	ObjectCollection* pObjectCollection;
	InputManager* pInputManager;
	SoundPlayer* pSoundPlayer;
	Camera* pCamera;
	SpriteCollection* pSpriteCollection;
	UIManager* pUIManager;
};