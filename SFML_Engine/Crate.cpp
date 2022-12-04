#include "Crate.h"

Crate::Crate(SpriteCollection* _pSpriteCollection, int _x, int _y) :
	Object(_x, _y, 20, 20, 0, immovable, true) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	spriteStack = SpriteStack(pSpriteCollection, "crate_stack_1", 10, 10, 6, 2);
	canBePickedUp = true;
	type = objectCrate;
}

void Crate::draw() {
	spriteStack.draw(boundingBox.x, boundingBox.y, boundingBox.h, rotation);
}