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
