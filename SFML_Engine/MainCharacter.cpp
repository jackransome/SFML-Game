#include "MainCharacter.h"

MainCharacter::MainCharacter(InputManager* _pInputManager, SpriteCollection *_pSpriteCollection, float x, float y) :
	Object(x, y, 32, 64, 0, true, true) {
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	animationRunLeft = SpriteSheet(pSpriteCollection, "mc_run_left", 22, 32, 6, 2);
	animationRunLeft.setChangeTimer(3);
	animationRunRight = SpriteSheet(pSpriteCollection, "mc_run_right", 22, 32, 6, 2);
	animationRunRight.setChangeTimer(3);
	animationWalkLeft = SpriteSheet(pSpriteCollection, "mc_walk_left", 16, 32, 4, 2);
	animationWalkLeft.setChangeTimer(6);
	animationWalkRight = SpriteSheet(pSpriteCollection, "mc_walk_right", 16, 32, 4, 2);
	animationWalkRight.setChangeTimer(6);
	animationWalkDown = SpriteSheet(pSpriteCollection, "mc_walk_front", 16, 32, 8, 2);
	animationWalkDown.setChangeTimer(6);
	animationWalkUp = SpriteSheet(pSpriteCollection, "mc_walk_back", 16, 32, 8, 2);
	animationWalkUp.setChangeTimer(6);
	animationBlink = SpriteSheet(pSpriteCollection, "mc_blink_1", 16, 32, 1, 2);
}

void MainCharacter::update() {
	boundingBox.xv = 0;
	boundingBox.yv = 0;

	if (pInputManager->isKeyDown(lShift)) {
		sprinting = true;
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
		sprinting = false;
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

	if (sprinting) {
		if (boundingBox.xv < 0) {
			animationRunLeft.run();
			animationRunLeft.draw(boundingBox.x, boundingBox.y, boundingBox.y);
		}
		else if (boundingBox.xv > 0) {
			animationRunRight.run();
			animationRunRight.draw(boundingBox.x, boundingBox.y, boundingBox.y);
		}
	}
	else {
		if (boundingBox.xv < 0) {
			animationWalkLeft.run();
			animationWalkLeft.draw(boundingBox.x, boundingBox.y, boundingBox.y);
		}
		else if (boundingBox.xv > 0) {
			animationWalkRight.run();
			animationWalkRight.draw(boundingBox.x, boundingBox.y, boundingBox.y);
		}
	}

	if (boundingBox.xv == 0) {
		if (boundingBox.yv > 0) {
			animationWalkDown.run();
			animationWalkDown.draw(boundingBox.x, boundingBox.y, boundingBox.y);
		}
		else if (boundingBox.yv < 0) {
			animationWalkUp.run();
			animationWalkUp.draw(boundingBox.x, boundingBox.y, boundingBox.y);
		}
		else {
			blinkCounter++;
			if (blinkCounter == 100) {
				blinkCounter = 0;

			}
			if (blinkCounter > 90) {
				animationBlink.drawFrame(boundingBox.x, boundingBox.y, boundingBox.y, 1);
			}
			else {
				animationBlink.drawFrame(boundingBox.x, boundingBox.y, boundingBox.y, 0);
			}
		}
	}

}
