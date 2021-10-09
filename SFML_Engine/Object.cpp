#include "Object.h"

Object::Object(float x, float y, float w, float h, float _z, bool _collidable, bool _hasGravity) {
	boundingBox.x = x;
	boundingBox.y = y;
	boundingBox.w = w;
	boundingBox.h = h;
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	z = _z;
	collidable = _collidable;
	hasGravity = _hasGravity;
}

BoundingBox Object::getBoundingBox() {
	return boundingBox;
}
BoundingBox* Object::getBoundingBoxPointer() {
	return &boundingBox;
}
void Object::update() {
	
}
void Object::draw() {

}