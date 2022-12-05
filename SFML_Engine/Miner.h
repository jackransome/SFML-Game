#pragma once
#include <glm/glm.hpp>
class Miner {
public:
	Miner(){};
	glm::vec2 getMinePoint() { return minePoint; };
	bool getIsMining() { return isMining;  };
	float getStrength() { return strength; }
protected:
	float strength = 0.1;
	bool isMining;
	glm::vec2 minePoint;
};