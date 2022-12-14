#pragma once

#include "Console.h"
#include "ObjectCollection.h"
#include "SpriteCollection.h"

class ControlSwitcher {
public:
	ControlSwitcher() {}
	ControlSwitcher(ObjectCollection* _pObjectCollection, Console* _pConsole, SpriteCollection* _pSpriteCollection);
	void drawOverlay();
	void setCurrentControlled(int ID);
	void switchControl();
	glm::vec2 getControlPosition();
	bool getControlling();
	void setControlling(bool _controlling);
private:
	bool controlling;
	int currentID = 0;
	int prospectiveID = -1;
	ObjectCollection* pObjectCollection;
	Console* pConsole;
	SpriteCollection* pSpriteCollection;
};