#pragma once
#include <glm/glm.hpp>
class Pickuper {
public:
	Pickuper();
	void setPickupPos(glm::vec2 _pickupPos);
	glm::vec2 getPickupPos();
	int getIdHeld();
	void setIdHeld(int _idHeld);
	void drop();
	bool getHolding();
protected:
	int idHeld;
	bool holding = false;
	glm::vec2 pickupPos = glm::vec2(-10000,-10000);
};