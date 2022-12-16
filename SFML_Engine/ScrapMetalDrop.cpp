#include "ScrapMetalDrop.h"

ScrapMetalDrop::ScrapMetalDrop(SpriteCollection* _pSpriteCollection, int _x, int _y) :
	Object(_x, _y, 24, 24, 0, movable, true) {
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
	spriteStack.draw(boundingBox.x, boundingBox.y, boundingBox.y, rotation);
}

void ScrapMetalDrop::update(){
	float speed = sqrt(boundingBox.xv * boundingBox.xv + boundingBox.yv * boundingBox.yv);
	if (speed > 5) {
		boundingBox.xv *= 10 / speed;
		boundingBox.yv *= 10 / speed;
	}
	boundingBox.xv *= 0.7;
	boundingBox.yv *= 0.7;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;

}
