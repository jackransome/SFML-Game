#pragma once

class PowerProducer {
public:
	PowerProducer(float _rate, bool* objectFlag);
	float getRate();
private:
	float rate;
};