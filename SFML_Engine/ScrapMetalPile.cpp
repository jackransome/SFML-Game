#include "ScrapMetalPile.h"

ScrapMetalPile::ScrapMetalPile(SpriteCollection* _pSpriteCollection, int _x, int _y) :
	Object(_x, _y, 32, 32, 0, immovable, true) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	spriteStack = SpriteStack(pSpriteCollection, "scrap_stack_1", 16, 16, 16, 2);
	canBePickedUp = true;
	type = objectCrate;
}

void ScrapMetalPile::draw() {
	rotation += 1;
	spriteStack.draw(boundingBox.x, boundingBox.y, boundingBox.h, rotation);
}