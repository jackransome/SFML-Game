#include "Object.h"

Object::Object(float x, float y, float w, float h, float _z, Collidability _collidability, bool _hasGravity) {
	boundingBox.x = x;
	boundingBox.y = y;
	boundingBox.w = w;
	boundingBox.h = h;
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	z = _z;
	collidability = _collidability;
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

bool Object::getToDestroy() {
	return toDestroy;
}

void Object::setToDestroy(bool _toDestroy) {
	toDestroy = _toDestroy;
}

int Object::getId() {
	return id;
}

void Object::setId(int _id) {
	id = _id;
}

void Object::setConsolePointer(Console* _pConsole) {
	pConsole = _pConsole;
}

Collidability Object::getCollidability() {
	return collidability;
}