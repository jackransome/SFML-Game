#pragma once
#include "Inventory.h"
#include "SpriteCollection.h"
#include "InputManager.h"



// Define a struct to hold your associated values
struct CostData {
	int scrap;
	int components;
	int other;
	ObjectType objectType;
};

enum class BuildType {
	turret, teleporter, relay
};

// Declare the map
extern std::map<BuildType, CostData> costMap;



class Builder {
public:
	Builder() {};
	Builder(SpriteCollection* _pSpriteCollection, Inventory* _pInventory, Console* _pConsole, InputManager* _pInputManager);
	void activate(BuildType buildType);
	void cancel();
	void update();
	bool getActive();
	void draw();
	bool checkResources(BuildType buildType);
private:
	bool mouseLDown = false;
	void buy(BuildType buildType);
	bool active = false;;
	BuildType currentBuildType;
	SpriteCollection* pSpriteCollection;
	Inventory* pInventory;
	Console* pConsole;
	InputManager* pInputManager;
};