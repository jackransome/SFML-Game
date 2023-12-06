#include "PowerProducer.h"

PowerProducer::PowerProducer(float _rate, bool* objectFlag){
	*objectFlag = true;
	rate = _rate;
}

float PowerProducer::getRate(){
	return rate;
}
