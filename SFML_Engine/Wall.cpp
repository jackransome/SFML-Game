#include "Wall.h"

Wall::Wall(SpriteCollection* _pSpriteCollection, int x, int y, int width, int height) :
	Object(x, y, width, height, 0, immovable, false) {
	pSpriteCollection = _pSpriteCollection;
	type = objectWall;
	sideImage = pSpriteCollection->getPointerFromName("wall_texture1");
	topImage = pSpriteCollection->getPointerFromName("platform_top_main");
	edgeImage = pSpriteCollection->getPointerFromName("platform_top_edge");
}

void Wall::draw() {
	//pSpriteCollection->addRectDraw(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, boundingBox.y, sf::Color(40, 40, 40, 255));
	pSpriteCollection->addImageDraw(sideImage, boundingBox.x, boundingBox.y + boundingBox.h - 50, boundingBox.y + boundingBox.h, 0, 0, boundingBox.w, 50, 1);
	//pSpriteCollection->addShaderToLast("test");
	pSpriteCollection->addImageDraw(edgeImage, boundingBox.x, boundingBox.y - 50, boundingBox.y + boundingBox.h, 2000 - boundingBox.w, 2000 - boundingBox.h, boundingBox.w, boundingBox.h, 1);
	//pSpriteCollection->addShaderToLast("test");
	pSpriteCollection->addImageDraw(topImage, boundingBox.x, boundingBox.y - 50, boundingBox.y + boundingBox.h, 0, 0, boundingBox.w, boundingBox.h, 1);
	//pSpriteCollection->addShaderToLast("test");
}