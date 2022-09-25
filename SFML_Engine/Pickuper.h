#pragma once
#include <glm/glm.hpp>
#include "Console.h"
class Pickuper {
public:
	Pickuper();
	void setPickupPos(glm::vec2 _pickupPos);
	glm::vec2 getPickupPos();
	int getIdHeld();
	void setIdHeld(int _idHeld);
	void drop();
	bool getHolding();
	void setTypeHeld(ObjectType _typeHeld);
	float getDropRotation();
protected:
	int idHeld;
	float dropRotation = 0;
	ObjectType typeHeld;
	bool holding = false;
	glm::vec2 pickupPos = glm::vec2(-10000,-10000);
};