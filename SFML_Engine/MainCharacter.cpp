#include "MainCharacter.h"

MainCharacter::MainCharacter(InputManager* _pInputManager, SpriteCollection *_pSpriteCollection, float x, float y) :
	Object(x, y, 32, 64, 0, true, true) {
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	animation1 = SpriteSheet(pSpriteCollection, "animation8", 22, 32, 6, 2);
	animation1.setChangeTimer(3);
}

void MainCharacter::update() {
	boundingBox.xv = 0;
	boundingBox.yv = 0;

	if (pInputManager->isKeyDown(lShift)) {
		if (pInputManager->isKeyDown(w)) {
			boundingBox.yv = -4;
		}
		if (pInputManager->isKeyDown(a)) {
			boundingBox.xv = -4;
		}
		if (pInputManager->isKeyDown(s)) {
			boundingBox.yv = 4;
		}
		if (pInputManager->isKeyDown(d)) {
			boundingBox.xv = 4;
		}
	}
	else {
		if (pInputManager->isKeyDown(w)) {
			boundingBox.yv = -2;
		}
		if (pInputManager->isKeyDown(a)) {
			boundingBox.xv = -2;
		}
		if (pInputManager->isKeyDown(s)) {
			boundingBox.yv = 2;
		}
		if (pInputManager->isKeyDown(d)) {
			boundingBox.xv = 2;
		}
	}
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}

void MainCharacter::draw() {
	animation1.run();
	animation1.draw(boundingBox.x, boundingBox.y, boundingBox.y);
}
