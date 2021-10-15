#include "Wall.h"

Wall::Wall(SpriteCollection* _pSpriteCollection, int x, int y, int width, int height) :
	Object(x, y, width, height, 0, immovable, false) {
	pSpriteCollection = _pSpriteCollection;
}

void Wall::draw() {
	pSpriteCollection->addRectDraw(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, boundingBox.y, sf::Color(40, 40, 40, 255));
}