#include "Pickuper.h"

Pickuper::Pickuper(){}

void Pickuper::setPickupPos(glm::vec2 _pickupPos){
	pickupPos = _pickupPos;
}

glm::vec2 Pickuper::getPickupPos(){
	return pickupPos;
}

int Pickuper::getIdHeld(){
	return idHeld;
}

void Pickuper::setIdHeld(int _idHeld){
	idHeld = _idHeld;
	holding = true;
}

void Pickuper::drop(){
	holding = false;
}

bool Pickuper::getHolding() {
	return holding;
}

void Pickuper::setTypeHeld(ObjectType _typeHeld){
	typeHeld = _typeHeld;
}

float Pickuper::getDropRotation(){
	return dropRotation;
}
