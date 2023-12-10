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
	CommandExecuter(ObjectCollection* _pObjectCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera, SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, UIManager* _pUIManager, Builder* _pBuilder, PowerManager* _pPowerManager);
	void execute(Command command);
	int getNextGameState();
private:
	ObjectCollection* pObjectCollection;
	InputManager* pInputManager;
	SoundPlayer* pSoundPlayer;
	Camera* pCamera;
	SpriteCollection* pSpriteCollection;
	UIManager* pUIManager;
	Builder* pBuilder;
	PowerManager* pPowerManager;
	int nextGameState = 0;
};