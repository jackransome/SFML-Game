#include "ResourceInventory.h"

ResourceInventory::ResourceInventory() {}

void ResourceInventory::addResources(Resource resource, int amount){
	resources[static_cast<int>(resource)] += amount;
}

int ResourceInventory::getResources(Resource resource){
	return resources[static_cast<int>(resource)];
}

bool ResourceInventory::removeResources(Resource resource, int amount)
{
	if (amount <= getResources(resource)) {
		resources[static_cast<int>(resource)] -= amount;
		return false;
	}
	else {
		return false;
	}
}

void ResourceInventory::clear(){
	for (int i = 0; i < numResourceTypes; i++) {
		resources[i] = 0;
	}
}

