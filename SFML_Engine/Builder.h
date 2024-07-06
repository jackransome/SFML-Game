#pragma once
#include "Inventory.h"
#include "SpriteCollection.h"
#include "InputManager.h"
#include "ObjectCollection.h"


// Define a struct to hold your associated values
struct CostData {
	int scrap;
	int components;
	int other;
	ObjectType objectType;
};

enum class BuildType {
	autoTurret, relay, generator, teleporterPillar, rover, buildDrone, count
};

// Declare the map
extern std::map<BuildType, CostData> costMap;



class Builder {
public:
	Builder() {};
	Builder(SpriteCollection* _pSpriteCollection, Inventory* _pInventory, Console* _pConsole, InputManager* _pInputManager, ObjectCollection* _pObjectCollection);
	void activate(BuildType buildType);
	void cancel();
	void update();
	bool getActive();
	void draw();
	bool checkResources(BuildType buildType);
	int getScrapNeeded(BuildType buildType);
	int getComponentsNeeded(BuildType buildType);
private:
	float rotation = 0;
	bool mouseLDown = false;
	void buy(BuildType buildType);
	bool active = false;;
	BuildType currentBuildType;
	SpriteCollection* pSpriteCollection;
	Inventory* pInventory;
	Console* pConsole;
	InputManager* pInputManager;
	ObjectCollection* pObjectCollection;
};