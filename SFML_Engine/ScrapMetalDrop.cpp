#include "ScrapMetalDrop.h"

ScrapMetalDrop::ScrapMetalDrop(SpriteCollection* _pSpriteCollection, int _x, int _y) :
	Object(_x, _y, 24, 24, 0, movable, true) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	spriteStack = SpriteStack(pSpriteCollection, "scrap_drop_stack_1", 12, 12, 10, 2);
	canBePickedUp = true;
	type = objectScrapMetalDrop;
	sellable = true;

	rotation = ((double)rand() / (RAND_MAX)) * 360;
}

void ScrapMetalDrop::draw() {
	spriteStack.draw(boundingBox.x, boundingBox.y + pConsole->getSinValue(bob_counter*58) *5, boundingBox.y, rotation);
}

void ScrapMetalDrop::update(){
	if (!pickedUp) {
		bob_counter += 0.1;
	}
	else {
		bob_counter = 0;
	}
}
