#pragma once
#include <vector>
#include "Item.h"
#include <iostream>

class Inventory {
public:
	Inventory();
	Inventory(int _slots, int _capacity, bool _multiples, bool toolOnly);
	~Inventory();
	int getSlots();
	int getMaxCapacity();
	int getCapacityUsed();
	bool getMultiples();
	int getAmount(int _index);
	Item* getItem(int _index);
	bool addItem(Item* _item);
	bool addItem(Item* _item, int index);
	int getSlotsUsed();
	Item* removeItem(int _index);
	int getCellsWidth();
	int getCellsHeight();
private:
	int slots;
	int capacity;
	bool multiples;
	std::vector<Item*> items;
	std::vector<int> amounts;
	bool toolOnly = false;
};