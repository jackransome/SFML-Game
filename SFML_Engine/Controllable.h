#pragma once

class Controllable {
public:
	Controllable(int _range);
	int getRange();
private:
	int range;
};