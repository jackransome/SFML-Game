#include "FootPrint.h"

FootPrint::FootPrint(SpriteCollection* _pSpriteCollection, float x, float y) :
	Decoration(_pSpriteCollection, x, y) {
	opacity = 100;
	decay = 0.95;
}

void FootPrint::draw() {
	pSpriteCollection->addRectDraw(boundingBox.x, boundingBox.y, 5, 5, -10000, sf::Color(0, 0, 0, opacity));
}

void FootPrint::update() {
	opacity *= decay;
	if (opacity < 3) {
		toDestroy = true;
	}
}
