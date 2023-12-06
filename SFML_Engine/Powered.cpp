#include "Powered.h"

Powered::Powered(float _capacity, float _charge, bool* objectFlag){
	capacity = _capacity;
	charge = _charge;
	*objectFlag = true;
}

void Powered::addCharge(float _amount) {
	charge += _amount;
}

float Powered::getChargePercentage(){
	return charge/capacity;
}

void Powered::changeCharge(float _amount){
	charge += _amount;
	if (charge < 0) {
		charge = 0;
	}
	else if (charge > capacity) {
		charge = capacity;
	}
}

bool Powered::hasCharge(){
	return charge;
}
