#include "InventoryPane.h"

InventoryPane::InventoryPane(int _x, int _y, Inventory* _pInventory, SpriteCollection* _pSpriteCollection) {
	pInventory = _pInventory;
	pSpriteCollection = _pSpriteCollection;
	x = _x;
	y = _y;
	cellsWidth = pInventory->getCellsWidth();
	cellsHeight = pInventory->getCellsHeight();
}

InventoryPane::~InventoryPane() {}

void InventoryPane::draw() {
	int sizeMinusGap = invCellSize - 2 * invCellGap;
	Item* tempItem;
	int cellX;
	int cellY;
	for (int i = 0; i < pInventory->getSlots(); i++) {
		
		cellX = x + (i % 4) * invCellSize;
		cellY = y + floor(float(i) / 4.0f) * invCellSize;
		pSpriteCollection->addImageDrawCut(pSpriteCollection->getPointerFromName("menu_pane"), cellX + invCellGap, cellY + invCellGap, 500000, 0, 0, sizeMinusGap, invCellBorder, 1, 0.2);
		pSpriteCollection->addImageDrawCut(pSpriteCollection->getPointerFromName("menu_pane"), cellX + invCellGap, cellY + invCellGap, 500000, 0, 0, invCellBorder, sizeMinusGap, 1, 0.2);
		if (pInventory->getSlotsUsed() > i && !(taken && takenIndex == i)) {
			tempItem = pInventory->getItem(i);
			tempItem->draw(cellX + invCellSize / 2, cellY + invCellSize / 2, 500000, 2);
		}
	}
}

int InventoryPane::getIndexFromMouse(int mouseX, int mouseY) {
	if ((mouseY - y) < 0 || (mouseX - x) < 0) return -1;
	int Xpos = floor((mouseX - x)/invCellSize);
	int Ypos = floor((mouseY - y) / invCellSize);
	if (Xpos < 0 || Xpos > (cellsWidth-1) || Ypos < 0 || Ypos > (cellsHeight-1)) return -1;
	return Xpos+Ypos*4;
}

void InventoryPane::setTaken(int _index) {
	takenIndex = _index;
	taken = true;
}

void InventoryPane::resetTaken() {
	taken = false;
}

Inventory* InventoryPane::getInventory() {
	return pInventory;
}
