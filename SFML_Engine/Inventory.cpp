#include "Inventory.h"

Inventory::Inventory(){}

Inventory::Inventory(int _slots, int _capacity, bool _multiples) {
	slots = _slots;
	capacity = _capacity;
	multiples = _multiples;
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

void Inventory::addItem(Item* _item) {
	if (getCapacityUsed() == capacity) {
		std::cout << "Capacity already reached\n";
		return;
	}
	bool alreadyExists = false;
	int index = -1;
	for (int i = 0; i < items.size(); i++) {
		if (items[i]->getType() == _item->getType() && items[i]->getCanStack()) {
			alreadyExists = true;
			index = i;
		}
	}
	if (multiples && alreadyExists) {
		amounts[index]++;
	}
	else {
		items.push_back(_item);
		amounts.push_back(1);
	}
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
