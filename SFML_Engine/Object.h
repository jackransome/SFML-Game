#pragma once
#include "BoundingBox.h"

class Object {
public:
	Object(float x, float y, float w, float h, float z, bool collidable, bool hasGravity);
	BoundingBox getBoundingBox();
	BoundingBox *getBoundingBoxPointer();
	virtual void update();
	virtual void draw();
protected:
	BoundingBox boundingBox;
	float z;
	bool collidable;
	bool hasGravity;
	
};