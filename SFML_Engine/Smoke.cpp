#include "Smoke.h"

Smoke::Smoke(SpriteCollection* _pSpriteCollection, float x, float y) :
	Decoration(_pSpriteCollection, x, y) {
	opacity = 0.3;
	decay = 0.97;
	type = objectFootprint;
	image = "decoration_smoke_" + std::to_string(rand()%4 + 1);
	rotation = rand() % 360;
}

void Smoke::draw() {
	pSpriteCollection->addRotatedImageDraw(pSpriteCollection->getPointerFromName(image), boundingBox.x - 7, boundingBox.y - 7 - height, -10000, 2, opacity, rotation, 8, 8, 14, 14);
}

void Smoke::update() {
	opacity *= decay;
	height++;
	if (opacity < 0.03) {
		toDestroy = true;
	}
}