#pragma once

class Mineable {
public:
	Mineable(float _toughness) { toughness = _toughness;  };
	void mine(float strength) { destructed -= strength / toughness; };
	bool getFullyMined() { return (destructed <= 0.0f); }
protected:
	float toughness;
	float destructed = 1.0f;
};