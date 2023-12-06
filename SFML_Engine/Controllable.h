#pragma once

class Controllable {
public:
	Controllable(int _range, bool* ObjectFlag);
	int getRange();
private:
	int range;
};