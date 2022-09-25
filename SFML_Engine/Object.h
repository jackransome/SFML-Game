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
	ObjectType getType();
	void setControlled(bool _controlled);
	bool getCanBePickedUp();
	bool getPickedUp();
	void setPickedUp(bool _pickedUp);
	int getPickedUpById();
	void setPickedUpById(int id);
	void setCenter(glm::vec2 _center);
	void setRotation(float _rotation);
	float getRotation(float _rotation);
protected:
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
	
	bool hasGravity;
};