#include "Inventory.h"

Inventory::Inventory() {}

void Inventory::addResources(Resource resource, int amount){
	resources[static_cast<int>(resource)] += amount;
}

int Inventory::getResources(Resource resource){
	return resources[static_cast<int>(resource)];
}

bool Inventory::removeResources(Resource resource, int amount)
{
	if (amount >= getResources(resource)) {
		resources[static_cast<int>(resource)] -= amount;
		return false;
	}
	else {
		return false;
	}
}

void Inventory::clear(){
	for (int i = 0; i < numResourceTypes; i++) {
		resources[i] = 0;
	}
}

