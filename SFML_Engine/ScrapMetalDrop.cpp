#include "ScrapMetalDrop.h"

ScrapMetalDrop::ScrapMetalDrop(SpriteCollection* _pSpriteCollection, int _x, int _y) :
	Object(_x, _y, 24, 24, 0, immovable, true) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	spriteStack = SpriteStack(pSpriteCollection, "scrap_drop_stack_1", 12, 12, 10, 2);
	canBePickedUp = true;
	type = objectCrate;
	sellable = true;
}

void ScrapMetalDrop::draw() {
	rotation += 2;
	spriteStack.draw(boundingBox.x, boundingBox.y, boundingBox.h, rotation);
}