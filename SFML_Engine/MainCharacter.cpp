#include "MainCharacter.h"

MainCharacter::MainCharacter(InputManager* _pInputManager, SpriteCollection *_pSpriteCollection, float x, float y) :
	Object(x, y, 32, 64, 0, movable, true),
	Living(100, 2) {
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	animationRunLeft = SpriteSheet(pSpriteCollection, "mc_run_left", 22, 32, 6, 2);
	animationRunLeft.setChangeTimer(3);
	animationRunRight = SpriteSheet(pSpriteCollection, "mc_run_right", 22, 32, 6, 2);
	animationRunRight.setChangeTimer(3);
	animationRunDown = SpriteSheet(pSpriteCollection, "mc_run_down", 16, 32, 12, 2);
	animationRunDown.setChangeTimer(3);
	animationWalkLeft = SpriteSheet(pSpriteCollection, "mc_walk_left", 16, 32, 4, 2);
	animationWalkLeft.setChangeTimer(4);
	animationWalkRight = SpriteSheet(pSpriteCollection, "mc_walk_right", 16, 32, 4, 2);
	animationWalkRight.setChangeTimer(4);
	animationWalkDown = SpriteSheet(pSpriteCollection, "mc_walk_front", 16, 32, 8, 2);
	animationWalkDown.setChangeTimer(6);
	animationWalkUp = SpriteSheet(pSpriteCollection, "mc_walk_back", 16, 32, 8, 2);
	animationWalkUp.setChangeTimer(6);
	animationBlink = SpriteSheet(pSpriteCollection, "mc_blink_1", 16, 32, 1, 2);
	imageStandBack = SpriteSheet(pSpriteCollection, "mc_stand_back", 16, 32, 1, 2);
	imageStandLeft = SpriteSheet(pSpriteCollection, "mc_stand_left", 16, 32, 1, 2);
	imageStandRight = SpriteSheet(pSpriteCollection, "mc_stand_right", 16, 32, 1, 2);
	direction = down;

	miniAnimation = SpriteSheet(pSpriteCollection, "mc_mini_run_right", 8, 20, 2, 2);
	miniAnimation.setChangeTimer(12);
}

void MainCharacter::update() {
	boundingBox.xv = 0;
	boundingBox.yv = 0;

	if (pInputManager->isKeyDown(lShift)) {
		vel = 4;
		sprinting = true;
	}
	else {
		vel = 2;
		sprinting = false;
	}
	if (pInputManager->isKeyDown(w)) {
		if (!pInputManager->isKeyDown(a) != !pInputManager->isKeyDown(d)) {
			if (pInputManager->isKeyDown(d)) {
				boundingBox.xv = vel * (1 / sqrt(2));
				direction = right;
			}
			else if (pInputManager->isKeyDown(a)) {
				direction = left;
				boundingBox.xv = -vel * (1 / sqrt(2));
			}
			boundingBox.yv = -vel*(1/sqrt(2));
		}
		else {
			boundingBox.yv = -vel;
			direction = up;
		}
	}
	else if (pInputManager->isKeyDown(s)) {
		if (!pInputManager->isKeyDown(a) != !pInputManager->isKeyDown(d)) {
			if (pInputManager->isKeyDown(d)) {
				boundingBox.xv = vel * (1 / sqrt(2));
				direction = right;
			}
			else if (pInputManager->isKeyDown(a)) {
				boundingBox.xv = -vel * (1 / sqrt(2));
				direction = left;
			}
			boundingBox.yv = vel * (1 / sqrt(2));
		}
		else {
			direction = down;
			boundingBox.yv = vel;
		}
	}
	else if (pInputManager->isKeyDown(a) && !pInputManager->isKeyDown(d)) {
		boundingBox.xv = -vel;
		direction = left;
	}
	else if (pInputManager->isKeyDown(d) && !pInputManager->isKeyDown(a)) {
		boundingBox.xv = vel;
		direction = right;
	}


	pConsole->addCommand(commandSetCameraPos, boundingBox.x, boundingBox.y);
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
	if ((boundingBox.xv || boundingBox.yv)) {
		pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x, boundingBox.y);
	}

}

void MainCharacter::draw() {
	if (sprinting) {
		if (boundingBox.xv < 0) {
			animationRunLeft.run();
			animationRunLeft.draw(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h);
		}
		else if (boundingBox.xv > 0) {
			animationRunRight.run();
			animationRunRight.draw(boundingBox.x-6, boundingBox.y, boundingBox.y + boundingBox.h);
		}
	}
	else {
		if (boundingBox.xv < 0) {
			animationWalkLeft.run();
			animationWalkLeft.draw(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h);
		}
		else if (boundingBox.xv > 0) {
			animationWalkRight.run();
			animationWalkRight.draw(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h);
		}
	}

	if (boundingBox.xv == 0) {
		if (boundingBox.yv == 0){
			switch (direction) {
			case up:
				imageStandBack.draw(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h);
				break;
			case down:
				blinkCounter++;
				if (blinkCounter == 100) {
					blinkCounter = 0;

				}
				if (blinkCounter > 90) {
					animationBlink.drawFrame(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h, 1);
				}
				else {
					animationBlink.drawFrame(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h, 0);
				}
				break;
			case left:
				imageStandLeft.draw(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h);
				break;
			case right:
				imageStandRight.draw(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h);
				break;

			}
		}
		if (sprinting) {
			if (boundingBox.yv > 0) {
				animationRunDown.run();
				animationRunDown.draw(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h);
			}
			else if (boundingBox.yv < 0) {
				animationWalkUp.run();
				animationWalkUp.draw(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h);
			}
		} else{
			if (boundingBox.yv > 0) {
				animationWalkDown.run();
				animationWalkDown.draw(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h);
			}
			else if (boundingBox.yv < 0) {
				animationWalkUp.run();
				animationWalkUp.draw(boundingBox.x, boundingBox.y, boundingBox.y + boundingBox.h);
			}
		}
	}

	miniAnimation.run();
	miniAnimation.draw(boundingBox.x-100, boundingBox.y-100, boundingBox.y + boundingBox.h);
}
