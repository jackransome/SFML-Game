#pragma once
#include "BoundingBox.h"
#include "Console.h"
#include "glm/glm.hpp"
#include <box2d/box2d.h>

enum Collidability { immovable, controllable, movable, none };

//enum ObjectType { none, player, enemy };

class Object {
public:
	Object(float x, float y, float w, float h, float z, Collidability _collidability, bool hasGravity, b2World* _pPhysicsWorld);
	~Object();
	BoundingBox getBoundingBox();
	BoundingBox *getBoundingBoxPointer();
	glm::vec2 getCenter();
	virtual void update();
	virtual void draw();
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
	b2Body* getPhysicsBody();
	bool hasBody();
	int getPhysicsBodyType();
protected:
	bool sellable = false;
	bool controlled = false;
	Console* pConsole;
	int id;
	bool toDestroy;
	BoundingBox boundingBox;
	bool canBePickedUp = false;
	bool pickedUp = false;
	int pickedUpById;
	float rotation = 0;
	float z;
	Collidability collidability;
	ObjectType type;
	bool hostile = false;
	b2Body* physicsBody;
	bool hasGravity;
	b2World* pPhysicsWorld;
	int physicsBodyType = 0;
};