#pragma once
#include <vector>
#include "SpriteCollection.h"
#include "Console.h"

class PowerNode {
public:

	PowerNode(Console* _pConsole, float _capacity, float _charge, bool* objectFlag, bool _distributor, float _dischargeRate, SpriteCollection* _pSpriteCollection, float _x, float _y) {
		*objectFlag = true;
		capacity = _capacity;
		charge = _charge;
		distributor = _distributor;
		dischargeRate = _dischargeRate;
		pSpriteCollection = _pSpriteCollection;
		updatePosition(_x, _y);
		ppConsole = _pConsole;
	}
	void addConnection(PowerNode* node);
	float getCapacityLeft();
	float getPercentage();
	void removeConnection(PowerNode* node);
	void distribute();
	void addCharge(float amount);
	void discharge(float amount);
	void updatePosition(float _x, float _y);
	void drawConections();
	glm::vec2 getPosition();
private:
	glm::vec2 position;
	std::vector<PowerNode*> connections;
	float capacity;
	float charge;
	bool distributor;
	float dischargeRate;
	SpriteCollection* pSpriteCollection;
	Console* ppConsole;
};