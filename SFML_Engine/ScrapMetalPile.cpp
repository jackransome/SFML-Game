#include "ScrapMetalPile.h"

ScrapMetalPile::ScrapMetalPile(SpriteCollection* _pSpriteCollection, int _x, int _y) :
	Object(_x, _y, 32, 32, 0, immovable, true
	),
	Mineable(10) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	spriteStack = SpriteStack(pSpriteCollection, "scrap_stack_1", 16, 16, 16, 2);
	//spriteStack.setRasterizeMode(true);
	canBePickedUp = false;
	type = objectScrapMetalPile;
}

void ScrapMetalPile::draw() {
	spriteStack.draw(boundingBox.x, boundingBox.y, boundingBox.y, rotation);
}