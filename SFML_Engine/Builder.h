#pragma once
#include "Inventory.h"
#include "SpriteCollection.h"
#include "InputManager.h"

enum class BuildType {
	turret, teleporter
};

class Builder {
public:
	Builder(SpriteCollection* _pSpriteCollection, Inventory* _pInventory, Console* _pConsole, InputManager* _pInputManager);
	bool hasResources(BuildType buildType);
	void activate(BuildType buildType);
	void cancel();
	void update();
	void draw();
private:
	void buy(BuildType buildType);
	bool active = false;;
	BuildType currentBuildType;
	SpriteCollection* pSpriteCollection;
	Inventory* pInventory;
	Console* pConsole;
	InputManager* pInputManager;
};