#pragma once
#include "SpriteCollection.h"
#include "Console.h"
#include "InputManager.h"
#include "ObjectCollection.h"


class PowerManager {
public:
	PowerManager() {};
	PowerManager(SpriteCollection* _pSpriteCollection, Console* _pConsole, InputManager* _pInputManager, ObjectCollection* _pObjectCollection, Camera* _pCamera);
	void activate();
	void cancel();
	void update();
	void draw();
private:
	bool active = false;
	SpriteCollection* pSpriteCollection;
	Console* pConsole;
	InputManager* pInputManager;
	Camera* pCamera;
	ObjectCollection* pObjectCollection;
	std::shared_ptr<Object> from;
	std::shared_ptr<Object> to;
	
};