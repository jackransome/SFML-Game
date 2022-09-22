#pragma once
#include "BoundingBox.h"
#include "Console.h"
#include "glm/glm.hpp"

enum Collidability { none, immovable, movable };

//enum ObjectType { none, player, enemy };

class Object {
public:
	Object(float x, float y, float w, float h, float z, Collidability _collidability, bool hasGravity);
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
	int getType();
	void setControlled(bool _controlled);
	bool getCanBePickedUp();
	bool getPickedUp();
	void setPickedUp(bool _pickedUp);
	void setCenter(glm::vec2 _center);
protected:
	bool controlled = false;
	Console* pConsole;
	int id;
	bool toDestroy;
	BoundingBox boundingBox;
	bool canBePickedUp = false;
	bool pickedUp = false;
	float z;
	Collidability collidability;
	int type = 0;
	
	bool hasGravity;
};