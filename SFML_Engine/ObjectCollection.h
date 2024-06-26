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
#include "DefenseOrb.h"
#include "Explosion.h"
#include "Smoke.h"
#include "Inventory.h"
#include "BuildDrone.h"
#include "Spark.h"
#include "Generator.h"
#include "EnemyBombRover.h"
#include "TeleporterPillar.h"
#include "Teleporter.h"
#include "EnemyTurretRover.h"
#include "PowerNode.h"
#include "Battery.h"

#include <unordered_map>
#include <array>

class ObjectCollection {
public:
	ObjectCollection();
	ObjectCollection(Console* _pConsole, InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera, Inventory* _pinventory);
	void draw();
	void update();
	void addMainCharacter(float x, float y);
	void addFootPrint(float x, float y);
	void addSmoke(float x, float y, float height, float scale);
	void addExplosion(float x, float y, float size);
	void addRoverTracks(float x, float y, float rotation);
	void addRoverTracksMini(float x, float y, float rotation);
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
	void addDefenseOrb(int x, int y);
	void addBuildDrone(int x, int y);
	void addSpark(int x, int y, int height, float colour);
	void addGenerator(int x, int y);
	void addEnemyBombRover(int x, int y);
	void addEnemyTurretRover(int x, int y);
	void addTeleporterPillar(int x, int y);
	void addBattery(int x, int y);
	void addTeleporter(int x, int y);
	void addProjectile(float _x, float _y, float _rotation, float _speed, int _fromID, int faction);
	void addBeam(float _x1, float _y1, float _x2, float _y2, int _fromID, int _faction);
	void setLatestId();
	void setLatestConsole();
	void runCollisionDetection(Object& o1, Object& o2);
	void drawHealthBars();
	void doAEODamage(float x, float y, float range, float damage, int faction);
	void doAEOHealing(float x, float y, float range, float amount, int faction);
	void setDebug(bool _debug);
	std::shared_ptr<Object> getTarget(glm::vec2 position,int faction, float range);
	void setCameraFocus(int id);
	void setControls(int id, bool controlled);
	void resetAllControls();
	void runPickUp(int id);
	void runDrop(int id);
	void runDropWithoutPickuper(int id);
	glm::vec2 getClosestControllablePosition(int currentID);
	int getClosestControllable(int currentID);
	std::shared_ptr<Object> getClosestPowerNode(int currentID);
	std::shared_ptr<Object> getClosestPowerNode();
	void pullToPoint(float x, float y, int range);
	std::shared_ptr<Object> getObjectById(int id);
	void setControlledDead(bool cd);
	bool getControlledDead();
	void clear();
	void AddToInventory(Resource resource, int amount);
	void setLastToBuild();
	int getGeneratorCount();
	void setLastRotation(float _rotation);
	bool checkArea(glm::vec4 _box);
	bool checkArea(glm::vec4 _box, int exclusionID1, int exclusionID2);
	void changeObjectCount(ObjectType type, int change);

	glm::vec2 getGeneratorPos();
private:
	void controlClosest();
	std::unordered_map<ObjectType, int> objectCounter;
	glm::vec2 generatorPos = glm::vec2(0);
	bool teleporterExists = false;
	bool controlledDead = false;
	bool debug = false;
	Console* pConsole;
	InputManager *pInputManager;
	SpriteCollection* pSpriteCollection;
	SoundPlayer* pSoundPlayer;
	Camera* pCamera;
	std::vector<std::shared_ptr<Object>> objects;
	std::vector< std::shared_ptr<Projectile>> projectiles;
	int maxBeams = 20;
	int numBeams = 0;
	std::array<glm::vec4, 20> beams;
	int beamsFrom[20];
	int beamsFaction[20];
	int numBeamsToDraw = 0;
	std::array<glm::vec4, 20> beamsToDraw;
	int cameraFocusId;
	int nextId = 0;
	int frame = 0;
	Inventory* pInventory;
};
