#pragma once

class Powered {
public:
	Powered(float _capacity, float _charge, bool* objectFlag);
	void addCharge(float _amount);
	float getChargePercentage();
	void changeCharge(float _amount);
	bool hasCharge();
private:
	float capacity;
	float charge;
};