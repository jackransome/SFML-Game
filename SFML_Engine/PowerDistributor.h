#pragma once

class PowerDistributor {
public:
	PowerDistributor(float _range, bool* objectFlag) {
		*objectFlag = true;
		range = _range;
	}
	float getRange() { return range; }
private:
	float range;
};