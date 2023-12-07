#pragma once
#include "BoundingBox.h"
#include "Console.h"
#include "glm/glm.hpp"

enum Collidability { immovable, controllable, movable, none, droneCol };

//enum ObjectType { none, player, enemy };

class Object {
public:
	Object(float x, float y, float w, float h, float z, Collidability _collidability, bool hasGravity);
	virtual ~Object();
	BoundingBox getBoundingBox();
	BoundingBox* getBoundingBoxPointer();
	glm::vec2 getCenter();
	virtual void update();
	virtual void draw();
	virtual void drawBuilding();
	bool getToDestroy();
	void setToDestroy(bool _toDestroy);
	int getId();
	void setId(int _id);
	void setConsolePointer(Console* _pConsole);
	Collidability getCollidability();
	ObjectType getType();
	void setControlled(bool _controlled);
	bool getControlled();
	bool getCanBePickedUp();
	bool getPickedUp();
	void setPickedUp(bool _pickedUp);
	int getPickedUpById();
	void setPickedUpById(int id);
	void setCenter(glm::vec2 _center);
	void setRotation(float _rotation);
	float getRotation(float _rotation);
	bool getSellable();
	bool getHostile();
	void push(float x, float y);
	int getPhysicsBodyType();
	bool getLiving();
	bool getIsEnemy();
	void setToBuild(bool _toBuild);
	bool getToBuild();
	bool incrementBuildProgress(float amount);
	int getBuildHeight();
	int getFaction();

	bool getIsPowered() { return isPowered; }
	bool getIsControllable() { return isControllable; }
	bool getIsPowerProducer() { return isPowerProducer; }
	bool getIsPowerDistributer() { return isPowerDistributer; }

	bool getHasTarget();
	float getTargetingRange();
protected:
	int faction = -1;
	bool toBuild = false;
	float buildTime = 1;
	float buildProgress = 0;;
	int buildHeight = 0;
	bool sellable = false;
	bool controlled = false;
	Console* pConsole;
	int id;
	bool toDestroy = false;
	BoundingBox boundingBox;
	bool canBePickedUp = false;
	bool pickedUp = false;
	int pickedUpById;
	float rotation = 0;
	float z;
	Collidability collidability;
	ObjectType type;
	bool hostile = false;
	bool isLiving = false;
	bool hasGravity;
	int physicsBodyType = 0;
	bool isEnemy = false;
	bool isPowered = false;
	bool isControllable = false;
	bool isPowerProducer = false;
	bool isPowerDistributer = false;
	bool hasTarget = false;
	float targetingRange = 0;
};