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
	void toggleActive();
	void cancel();
	void update();
	void draw();
	bool isActive();
private:
	int maxLength = 250;
	bool active = false;
	SpriteCollection* pSpriteCollection;
	Console* pConsole;
	InputManager* pInputManager;
	Camera* pCamera;
	ObjectCollection* pObjectCollection;
	std::weak_ptr<Object> from;
	std::shared_ptr<Object> to;
	
};