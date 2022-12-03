#include "Controllable.h"

Controllable::Controllable(int _range) {
	range = _range;
}

int Controllable::getRange() {
	return range;
}