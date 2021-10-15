#pragma once
#include "Object.h"
#include "InputManager.h"
#include "SpriteCollection.h"
#include "SoundPlayer.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "FootPrint.h"

class ObjectCollection {
public:
	ObjectCollection();
	ObjectCollection(Console* _pConsole, InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera);
	void draw();
	void update();
	void addMainCharacter(float x, float y);
	void addFootPrint(float x, float y);
	void setLatestId();
	void setLatestConsole();
private:
	Console* pConsole;
	InputManager *pInputManager;
	SpriteCollection* pSpriteCollection;
	SoundPlayer* pSoundPlayer;
	Camera* pCamera;
	std::vector<Object*> objects;

	int nextId = 0;
};
