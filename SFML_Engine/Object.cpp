#include "Object.h"

Object::Object(float x, float y, float w, float h, float _z, Collidability _collidability, bool _hasGravity) {
	boundingBox.x = x - w/2;
	boundingBox.y = y - h/2;
	boundingBox.w = w;
	boundingBox.h = h;
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	z = _z;
	collidability = _collidability;
	hasGravity = _hasGravity;
}

Object::~Object(){
}

BoundingBox Object::getBoundingBox() {
	return boundingBox;
}
BoundingBox* Object::getBoundingBoxPointer() {
	return &boundingBox;
}
glm::vec2 Object::getCenter()
{
	return glm::vec2(boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2);
}
void Object::update() {
	
}
void Object::draw() {

}

void Object::drawBuilding() {}

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

bool Object::getControlled(){
	return controlled;
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

bool Object::getHostile(){
	return hostile;
}

void Object::push(float x, float y){
	boundingBox.xv += x;
	boundingBox.yv += y;
}

int Object::getPhysicsBodyType(){
	// 0 = none
	// 1 = kinematic
	// 2 = dynamic
	return physicsBodyType;
}

bool Object::getLiving(){
	return isLiving;
}

bool Object::getIsEnemy(){
	return isEnemy;
}

void Object::setToBuild(bool _toBuild){
	toBuild = _toBuild;
}

bool Object::getToBuild() {
	return toBuild;
}

bool Object::incrementBuildProgress(float amount){
	buildProgress += amount*(1.0/buildTime);
	if (buildProgress >= 1) {
		toBuild = false;
		justBuilt = true;
		return true;
	}
	return false;
}

int Object::getBuildHeight(){
	return buildHeight;
}

int Object::getFaction(){
	return faction;
}

bool Object::getHasTarget(){
	return hasTarget;
}

float Object::getTargetingRange(){
	return targetingRange;
}

bool Object::getJustBuilt(){
	return justBuilt;
}

void Object::resetJustBuilt(){
	justBuilt = false;
}

bool Object::getFullyCharged(){
	return fullyCharged;
}

bool Object::getHasInventory() {
	return hasInventory;
}

Inventory* Object::getInventory() {
	return inventory;
}

Inventory* Object::getToolbar() {
	return toolbar;
}

int Object::getToolSelected() {
	return toolSelected;
}

void Object::changeToolSelected(int _newTool) {
	toolSelected = _newTool;
	if (toolSelected >= toolbar->getSlotsUsed()) {
		toolSelected = toolbar->getSlotsUsed()-1;
	}
	holdingTool = true;
}

void Object::incrementToolSelected(int _amount) {
	toolSelected += _amount;
	while (toolSelected >= toolbar->getSlotsUsed()) {
		toolSelected -= toolbar->getSlotsUsed();
	}
	holdingTool = true;
}
