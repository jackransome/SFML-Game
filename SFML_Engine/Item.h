#pragma once

class Item {
public:
	Item();
	~Item();
	virtual void draw() = 0;
	bool getIsTool();
private:
	bool isTool = false;
};