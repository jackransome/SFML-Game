#pragma once
#include "Console.h"

const int numResourceTypes = static_cast<int>(Resource::count);

class ResourceInventory {
public:
	ResourceInventory();
	void addResources(Resource resource, int amount);
	int getResources(Resource resource);
	bool removeResources(Resource resource, int amount);
	void clear();
private:
	int resources[numResourceTypes] = { 0 };
};