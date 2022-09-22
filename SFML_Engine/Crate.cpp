#include "Crate.h"

Crate::Crate(SpriteCollection* _pSpriteCollection, int _x, int _y) :
	Object(x, y, 20, 20, 0, movable, true),
	Living(100, 2) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	spriteStack = SpriteStack(pSpriteCollection, "crate_stack_1", 10, 10, 6, 2);
	canBePickedUp = true;
}

void Crate::draw() {
	spriteStack.draw(boundingBox.x, boundingBox.y, boundingBox.h, 0);
}