#pragma once

#include "Inventory.h"
#include "SpriteCollection.h"

class InventoryPane {
public:
	InventoryPane(int _x, int _y, Inventory* _pInventory, SpriteCollection* _pSpriteCollection);
	~InventoryPane();
	void draw();
	int getIndexFromMouse(int mouseX, int mouseY);
	void setTaken(int _index);
	void resetTaken();
	Inventory* getInventory();
private:
	Inventory* pInventory;
	SpriteCollection* pSpriteCollection;
	bool taken;
	int takenIndex;
	int invCellSize = 96;
	int invCellGap = 4;
	int invCellBorder = 8;
	int x;
	int y;
	int cellsWidth;
	int cellsHeight;
};