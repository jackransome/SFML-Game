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
#include "ScrapMetalPile.h"
#include "ScrapMetalDrop.h"
#include "MarketRelay.h"
#include "AutoTurret.h"
#include "Projectile.h"
#include "Jammer.h"

class ObjectCollection {
public:
	ObjectCollection();
	ObjectCollection(Console* _pConsole, InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera, b2World* _pPhysicsWorld);
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
	void addScapMetalPile(int x, int y);
	void addScapMetalDrop(int x, int y);
	void addMarketRelay(int x, int y);
	void addAutoTurret(int x, int y);
	void addJammer(int x, int y);
	void addProjectile(float _x, float _y, float _rotation, float _speed, int _fromID);
	void setLatestId();
	void setLatestConsole();
	void runCollisionDetection();
	void drawHealthBars();
	void doAEODamage(float x, float y, float range, float damage, int id);
	void setDebug(bool _debug);
	void setEnemyTarget(int x, int y, float xv, float yv);
	glm::vec4 getTarget(glm::vec2 position, FactionIdentifier faction);
	void setCameraFocus(int id);
	void setControls(int id, bool controlled);
	void resetAllControls();
	void runPickUp(int id);
	void runDrop(int id);
	void runDropWithoutPickuper(int id);
	int getClosestControllable(int currentID);
	void pullToPoint(float x, float y, int range);
	void sellObjects(float startX, float startY, float endX, float endY, int marketRelayID);
	Object* getObjectById(int id);
	void setControlledDead(bool cd);
	bool getControlledDead();
	void clear();
	

private:
	bool controlledDead = false;
	bool debug = false;
	Console* pConsole;
	InputManager *pInputManager;
	SpriteCollection* pSpriteCollection;
	SoundPlayer* pSoundPlayer;
	Camera* pCamera;
	std::vector<Object*> objects;
	std::vector<Projectile*> projectiles;
	int cameraFocusId;
	int nextId = 0;
	int frame = 0;
	b2World* pPhysicsWorld;

	void freeObjectMemory(int index);

};
