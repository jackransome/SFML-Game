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

class ObjectCollection {
public:
	ObjectCollection();
	ObjectCollection(Console* _pConsole, InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera);
	void draw();
	void update();
	void addMainCharacter(float x, float y);
	void addFootPrint(float x, float y);
	void addAction1Animation(float x, float y);
	void addWall(int x, int y, int w, int h);
	void addEnemy(int x, int y);
	void setLatestId();
	void setLatestConsole();
	void runCollisionDetection();
	void drawHealthBars();
	void doAEODamage(float x, float y, float range, float damage);
	void setDebug(bool _debug);
	void setEnemyTarget(int x, int y);
private:
	bool debug = false;
	Console* pConsole;
	InputManager *pInputManager;
	SpriteCollection* pSpriteCollection;
	SoundPlayer* pSoundPlayer;
	Camera* pCamera;
	std::vector<Object*> objects;

	int nextId = 0;
};
