#include "Inventory.h"

Inventory::Inventory(){}

Inventory::Inventory(int _slots, int _capacity, bool _multiples, bool _toolOnly) {
	slots = _slots;
	capacity = _capacity;
	multiples = _multiples;
	toolOnly = _toolOnly;
}

Inventory::~Inventory() {}

int Inventory::getSlots() {
	return slots;
}

int Inventory::getMaxCapacity() {
	return capacity;
}

int Inventory::getCapacityUsed() {
	int total = 0;
	for (int i = 0; i < amounts.size(); i++) {
		total += amounts[i];
	}
	return total;
}

bool Inventory::getMultiples() {
	return multiples;
}

int Inventory::getAmount(int _index) {
	if (_index >= items.size()) {
		std::cout << "Item index too high\n";
		return -1;
	}
	return amounts[_index];
}

Item* Inventory::getItem(int _index) {
	if (_index >= items.size()) {
		std::cout << "Item index too high\n";
		return nullptr;
	}
	return items[_index];
}

bool Inventory::addItem(Item* _item) {
	return addItem(_item, 1000);
}

bool Inventory::addItem(Item* _item, int _index) {
	if (toolOnly && !_item->getIsTool()) return false;
	if (getCapacityUsed() == capacity) return false;

	bool alreadyExists = false;
	int index = -1;
	for (int i = 0; i < items.size(); i++) {
		if (items[i]->getType() == _item->getType() && items[i]->getCanStack()) {
			alreadyExists = true;
			index = i;
		}
	}
	if (multiples && alreadyExists && _item->getCanStack()) {
		amounts[index]++;
	}
	else {
		if (items.size() == slots) {
			return false;
		}
		else {
			if (_index >= items.size()) {
				items.push_back(_item);
				amounts.push_back(1);
			}
			else {
				items.insert(items.begin() + _index, _item);
				amounts.insert(amounts.begin() + _index, 1);
			}
		}

	}
	return true;
}

int Inventory::getSlotsUsed() {
	return items.size();;
}

Item* Inventory::removeItem(int _index) {
	if (_index >= items.size()) {
		std::cout << "Item index too high\n";
		return nullptr;
	}
	Item* temp = items[_index];
	items.erase(items.begin() + _index);
	amounts.erase(amounts.begin() + _index);
	return temp;
}

int Inventory::getCellsWidth() {
	return std::min(4, slots);
}

int Inventory::getCellsHeight() {
	return ceil(float(slots)/4.0f);
}
