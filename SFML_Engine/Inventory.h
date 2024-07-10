#pragma once
#include <vector>
#include "Item.h"
#include <iostream>

class Inventory {
public:
	Inventory();
	Inventory(int _slots, int _capacity, bool _multiples);
	~Inventory();
	int getSlots();
	int getMaxCapacity();
	int getCapacityUsed();
	bool getMultiples();
	int getAmount(int _index);
	Item* getItem(int _index);
	void addItem(Item* _item);
	Item* removeItem(int _index);
private:
	int slots;
	int capacity;
	bool multiples;
	std::vector<Item*> items;
	std::vector<int> amounts;
};