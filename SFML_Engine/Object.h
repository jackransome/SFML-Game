#pragma once
#include "BoundingBox.h"
#include "Console.h"

enum Collidability { none, immovable, movable };

class Object {
public:
	Object(float x, float y, float w, float h, float z, Collidability _collidability, bool hasGravity);
	BoundingBox getBoundingBox();
	BoundingBox *getBoundingBoxPointer();
	virtual void update();
	virtual void draw();
	bool getToDestroy();
	void setToDestroy(bool _toDestroy);
	int getId();
	void setId(int _id);
	void setConsolePointer(Console* _pConsole);
	Collidability getCollidability();
protected:
	Console* pConsole;
	int id;
	bool toDestroy;
	BoundingBox boundingBox;
	float z;
	Collidability collidability;

	bool hasGravity;
};