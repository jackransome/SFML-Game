#pragma once
#include <vector>
#include "SpriteCollection.h"
#include "Console.h"

class PowerNode {
public:

	PowerNode(Console* _pConsole, float _capacity, float _charge, bool* objectFlag, bool _distributor, bool _generator, float _dischargeRate, SpriteCollection* _pSpriteCollection, float _x, float _y, int* _idPointer) {
		*objectFlag = true;
		capacity = _capacity;
		charge = _charge;
		distributor = _distributor;
		dischargeRate = _dischargeRate;
		pSpriteCollection = _pSpriteCollection;
		updatePowerPosition(_x, _y);
		ppConsole = _pConsole;
		idPointer = _idPointer;
		generator = _generator;
	}
	bool getGenerator();
	bool getBuilt();
	void setBuilt();
	void removeConnection(int _id);
	void addConnection(PowerNode* node);
	float getCapacityLeft();
	float getPercentage();
	void removeConnection(PowerNode* node);
	void distribute();
	void addCharge(float amount);
	void discharge(float amount);
	void updatePowerPosition(float _x, float _y);
	void drawPowerConections();
	glm::vec2 getPosition();
	int getPowerId();
	void removeFromConnections();
private:
	int maxLength = 250;
	bool generator;
	bool built = false;
	glm::vec2 position;
	std::vector<PowerNode*> connections;
	float capacity;
	float charge;
	bool distributor;
	float dischargeRate;
	SpriteCollection* pSpriteCollection;
	Console* ppConsole;
	int* idPointer = nullptr;
};