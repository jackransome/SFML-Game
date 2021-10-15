#pragma once
#include "BoundingBox.h"
#include "Console.h"

class Object {
public:
	Object(float x, float y, float w, float h, float z, bool collidable, bool hasGravity);
	BoundingBox getBoundingBox();
	BoundingBox *getBoundingBoxPointer();
	virtual void update();
	virtual void draw();
	bool getToDestroy();
	void setToDestroy(bool _toDestroy);
	int getId();
	void setId(int _id);
	void setConsolePointer(Console* _pConsole);
protected:
	Console* pConsole;
	int id;
	bool toDestroy;
	BoundingBox boundingBox;
	float z;
	bool collidable;
	bool hasGravity;
};