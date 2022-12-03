#pragma once
#include "Object.h"
#include "InputManager.h"
#include "SpriteCollection.h"
#include "SoundPlayer.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "FootPrint.h"
#include "Wall.h"
#include "Enemy.h"
#include "Rover.h";
#include "Crate.h"
#include "RoverTracks.h"
#include "Relay.h"

class ObjectCollection {
public:
	ObjectCollection();
	ObjectCollection(Console* _pConsole, InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera);
	void draw();
	void update();
	void addMainCharacter(float x, float y);
	void addFootPrint(float x, float y);
	void addRoverTracks(float x, float y, float rotation);
	void addAction1Animation(float x, float y);
	void addWall(int x, int y, int w, int h);
	void addEnemy(int x, int y);
	void addRover(int x, int y);
	void addCrate(int x, int y);
	void addRelay(int x, int y);
	void setLatestId();
	void setLatestConsole();
	void runCollisionDetection();
	void drawHealthBars();
	void doAEODamage(float x, float y, float range, float damage);
	void setDebug(bool _debug);
	void setEnemyTarget(int x, int y);
	void setCameraFocus(int id);
	void setControls(int id, bool controlled);
	void resetAllControls();
	void runPickUp(int id);
	void runDrop(int id);
	int getClosestControllable(int currentID);
	Object* getObjectById(int id);

private:
	bool debug = false;
	Console* pConsole;
	InputManager *pInputManager;
	SpriteCollection* pSpriteCollection;
	SoundPlayer* pSoundPlayer;
	Camera* pCamera;
	std::vector<Object*> objects;
	int cameraFocusId;
	int nextId = 0;
};
