#include "Smoke.h"

Smoke::Smoke(SpriteCollection* _pSpriteCollection, float x, float y, float _height, float _scale) :
	Decoration(_pSpriteCollection, x, y) {
	//opacity = 0.3;
	opacity = 0.25 + 0.5 * (rand() % 10) / 10;
	decay = 0.975 - float(rand() % 8) * 0.025;
	riseSpeed = 0.75 + float(rand() % 8) / 8;
	type = objectSmoke;
	image = "decoration_smoke_" + std::to_string(rand()%4 + 1);
	rotation = rand() % 360;
	height = _height;
	scale = _scale;
}

void Smoke::draw() {
	pSpriteCollection->addRotatedImageDraw(pSpriteCollection->getPointerFromName(image), boundingBox.x - 7, boundingBox.y - 7 - height, boundingBox.y - 7, scale, opacity, rotation, 8, 8, 14, 14);
}

void Smoke::update() {
	opacity *= decay;
	height += riseSpeed;
	if (opacity < 0.03) {
		toDestroy = true;
	}
}