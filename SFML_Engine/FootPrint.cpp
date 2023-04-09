#include "FootPrint.h"

FootPrint::FootPrint(SpriteCollection* _pSpriteCollection, float x, float y) :
	Decoration(_pSpriteCollection, x, y) {
	opacity = 50;
	decay = 0.97;
	type = objectFootprint;
}

void FootPrint::draw() {
	//pSpriteCollection->addRectDraw(boundingBox.x, boundingBox.y, 16, 16, -10000, sf::Color(0, 0, 0, opacity));
	pSpriteCollection->addCircleDraw(boundingBox.x-8, boundingBox.y-8, 8, -10000, sf::Color(0, 0, 0, opacity));
}

void FootPrint::update() {
	opacity *= decay;
	if (opacity < 3) {
		toDestroy = true;
	}
}


Action1Animation::Action1Animation(SpriteCollection* _pSpriteCollection, float _x, float _y) :
	Decoration(_pSpriteCollection, x, y) {
	ss = SpriteSheet(pSpriteCollection, "action1", 8, 8, 4, 2);
	ss.setChangeTimer(2);
	x = _x;
	y = _y;
}

void Action1Animation::draw() {
	ss.draw(x, y, 0);
	ss.run();
}

void Action1Animation::update() {
	if (ss.isComplete()) {
		toDestroy = true;
	}
}
