#pragma once

#include "Console.h"
#include "ObjectCollection.h"
#include "SpriteCollection.h"
#include "InputManager.h"

class ControlSwitcher {
public:
	ControlSwitcher() {}
	ControlSwitcher(ObjectCollection* _pObjectCollection, Console* _pConsole, SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Camera* _pCamera);
	void setCurrentControlled(int ID);
	void handleInput();
	void draw();
	void switchControl();
	glm::vec2 getControlPosition();
	bool getControlling();
	void setControlling(bool _controlling);
	Inventory* getControllingInventory();
private:
	bool active = false;;
	bool controlling;
	int currentID = 0;
	int prospectiveID = -1;
	ObjectCollection* pObjectCollection;
	Console* pConsole;
	SpriteCollection* pSpriteCollection;
	InputManager* pInputManager;
	Camera* pCamera;
};