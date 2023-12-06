#include "Controllable.h"

Controllable::Controllable(int _range, bool* ObjectFlag) {
	range = _range;
	*ObjectFlag = true;
}

int Controllable::getRange() {
	return range;
}