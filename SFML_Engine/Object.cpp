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
glm::vec2 Object::getCenter()
{
	return glm::vec2(boundingBox.x + boundingBox.w/2, boundingBox.y + boundingBox.h / 2);
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

ObjectType Object::getType(){
	return type;
}

void Object::setControlled(bool _controlled){
	controlled = _controlled;
}

bool Object::getCanBePickedUp()
{
	return canBePickedUp;
}

bool Object::getPickedUp(){
	return pickedUp;
}

void Object::setPickedUp(bool _pickedUp){
	pickedUp = _pickedUp;
}

int Object::getPickedUpById()
{
	return pickedUpById;
}

void Object::setPickedUpById(int id){
	pickedUpById = id;
}

void Object::setCenter(glm::vec2 _center){
	boundingBox.x = _center.x - boundingBox.w / 2;
	boundingBox.y = _center.y - boundingBox.h / 2;
}

void Object::setRotation(float _rotation){
	rotation = _rotation;
}

float Object::getRotation(float _rotation){
	return rotation;
}

bool Object::getSellable(){
	return sellable;
}
