#include "MainCharacter.h"

MainCharacter::MainCharacter(InputManager* _pInputManager, SpriteCollection *_pSpriteCollection, float x, float y) :
	Object(x, y, 16, 16, 0, movable, true),
	Living(100, 2),
	Controllable(200) {
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	animationRunLeft = SpriteSheet(pSpriteCollection, "mc_run_left", 22, 32, 6, 2);
	animationRunLeft.setChangeTimer(3);
	animationRunRight = SpriteSheet(pSpriteCollection, "mc_run_right", 22, 32, 6, 2);
	animationRunRight.setChangeTimer(3);
	animationRunDown = SpriteSheet(pSpriteCollection, "mc_run_down", 16, 32, 12, 2);
	animationRunDown.setChangeTimer(3);
	animationRunUp = SpriteSheet(pSpriteCollection, "mc_run_up", 16, 32, 12, 2);
	animationRunUp.setChangeTimer(3);
	animationWalkLeft = SpriteSheet(pSpriteCollection, "mc_walk_left", 16, 32, 4, 2);
	animationWalkLeft.setChangeTimer(4);
	animationWalkRight = SpriteSheet(pSpriteCollection, "mc_walk_right", 16, 32, 4, 2);
	animationWalkRight.setChangeTimer(4);
	animationWalkDown = SpriteSheet(pSpriteCollection, "mc_walk_front", 16, 32, 8, 2);
	animationWalkDown.setChangeTimer(4);
	animationWalkUp = SpriteSheet(pSpriteCollection, "mc_walk_back", 16, 32, 8, 2);
	animationWalkUp.setChangeTimer(4);
	animationBlink = SpriteSheet(pSpriteCollection, "mc_blink_1", 16, 32, 1, 2);
	imageStandBack = SpriteSheet(pSpriteCollection, "mc_stand_back", 16, 32, 1, 2);
	imageStandLeft = SpriteSheet(pSpriteCollection, "mc_stand_left", 16, 32, 1, 2);
	imageStandRight = SpriteSheet(pSpriteCollection, "mc_stand_right", 16, 32, 1, 2);
	direction = down;

	type = objectMainCharacter;

	miniAnimation = SpriteSheet(pSpriteCollection, "mc_mini_run_right", 8, 20, 2, 2);
	miniAnimation.setChangeTimer(12);
}

void MainCharacter::update() {
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	if (controlled) {
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
				boundingBox.yv = -vel * (1 / sqrt(2));
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
	}
	
	//pConsole->addCommand(commandSetCameraPos, boundingBox.x, boundingBox.y);
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
	if ((boundingBox.xv || boundingBox.yv) && pConsole->getFrame() % 9 == 0) {

	}
}

void MainCharacter::draw() {
	eyeVisible1 = false;
	eyeVisible2 = false;
	if (pInputManager->isKeyDown(y)) {
		pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x, boundingBox.y), glm::vec3(255, 255, 255), 0.5, 0, false);
	}
	if (sprinting) {
		if (boundingBox.xv < 0) {
			animationRunLeft.run();
			animationRunLeft.draw(boundingBox.x-8-6, boundingBox.y-48, boundingBox.y + boundingBox.h);
			if (animationRunLeft.getFrame() == 0 || animationRunLeft.getFrame() == 3) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 19);
				eyePosition2 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 19);
			}
			else if (animationRunLeft.getFrame() == 1 || animationRunLeft.getFrame() == 2) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 21);
				eyePosition2 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 21);
			}
			else {
				eyePosition1 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 17);
				eyePosition2 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 17);
			}
			eyeVisible1 = true;
			if (animationRunLeft.getChangedFrame() && animationRunLeft.getFrame() == 1) {
				pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2 - 10, boundingBox.y + boundingBox.h / 2 + 6);
				pConsole->addCommand(commandPlaySound, "footstep_snow");
			}
		}
		else if (boundingBox.xv > 0) {
			animationRunRight.run();
			animationRunRight.draw(boundingBox.x- 8-6, boundingBox.y - 48, boundingBox.y + boundingBox.h);
			if (animationRunRight.getFrame() == 0 || animationRunRight.getFrame() == 3) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 - 6 + 39, boundingBox.y - 48 + 19);
				eyePosition2 = glm::vec2(boundingBox.x - 8 - 6 + 39, boundingBox.y - 48 + 19);
			}
			else if (animationRunRight.getFrame() == 1 || animationRunRight.getFrame() == 2) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 - 6 + 39, boundingBox.y - 48 + 21);
				eyePosition2 = glm::vec2(boundingBox.x - 8 - 6 + 39, boundingBox.y - 48 + 19);
			}
			else {
				eyePosition1 = glm::vec2(boundingBox.x - 8 - 6 + 39, boundingBox.y - 48 + 17);
				eyePosition2 = glm::vec2(boundingBox.x - 8 - 6 + 39, boundingBox.y - 48 + 19);
			}
			eyeVisible1 = true;
			if (animationRunRight.getChangedFrame() && animationRunRight.getFrame() == 1) {
				pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2 + 10, boundingBox.y + boundingBox.h / 2 + 6);
				pConsole->addCommand(commandPlaySound, "footstep_snow");
			}
		}
	}
	else {
		if (boundingBox.xv < 0) {
			animationWalkLeft.run();
			animationWalkLeft.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
			if (animationWalkLeft.getFrame() == 0 || animationWalkLeft.getFrame() == 2) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 13);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 13);
			}
			else if (animationWalkLeft.getFrame() == 1) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 15);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 15);
			}
			else {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 11);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 11);
			}
			eyeVisible1 = true;
			if (animationWalkLeft.getChangedFrame() && animationWalkLeft.getFrame() == 1) {
				pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2 - 6, boundingBox.y + boundingBox.h / 2+6);
				pConsole->addCommand(commandPlaySound, "footstep_snow");
			}
		}
		else if (boundingBox.xv > 0) {
			animationWalkRight.run();
			animationWalkRight.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
			if (animationWalkRight.getFrame() == 0 || animationWalkRight.getFrame() == 2) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 13);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 13);
			}
			else if (animationWalkRight.getFrame() == 1) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 15);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 15);
			}
			else {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 11);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 11);
			}
			eyeVisible1 = true;
			if (animationWalkRight.getChangedFrame() && animationWalkRight.getFrame() == 1) {
				pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2 +6, boundingBox.y + boundingBox.h / 2 + 6);
				pConsole->addCommand(commandPlaySound, "footstep_snow");
			}
		}
	}
	if (boundingBox.xv == 0) {
		if (boundingBox.yv == 0){
			switch (direction) {
			case up:
				imageStandBack.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y+ boundingBox.h);
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
				break;
			case down:
				blinkCounter++;
				if (blinkCounter == 173) {
					blinkCounter = 0;

				}
				if (blinkCounter > 160) {
					animationBlink.drawFrame(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h, 1);
				}
				else {
					animationBlink.drawFrame(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h, 0);
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
					eyeVisible1 = true;
					eyeVisible2 = true;

				}
				break;
			case left:
				eyeVisible1 = true;
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 13);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 13);
				imageStandLeft.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				break;
			case right:
				eyeVisible1 = true;
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 13);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 13);
				imageStandRight.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				break;

			}
		}
		if (sprinting) {
			if (boundingBox.yv > 0) {
				animationRunDown.run();
				animationRunDown.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				if ((animationRunDown.getFrame() > 0 && animationRunDown.getFrame() < 4) || (animationRunDown.getFrame() > 6 && animationRunDown.getFrame() < 10)) {
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 15);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 15);
				}
				else {
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
				}

				eyeVisible1 = true;
				eyeVisible2 = true;
				if (animationRunDown.getChangedFrame() && (animationRunDown.getFrame() == 0 || animationRunDown.getFrame() == 6)) {
					pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 + 6);
					pConsole->addCommand(commandPlaySound, "footstep_snow");
				}
			}
			else if (boundingBox.yv < 0) {
				animationRunUp.run();
				animationRunUp.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				if ((animationRunDown.getFrame() > 0 && animationRunDown.getFrame() < 4) || (animationRunDown.getFrame() > 6 && animationRunDown.getFrame() < 10)) {
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 15);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 15);
				}
				else {
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
				}
				if (animationRunUp.getChangedFrame() && (animationRunUp.getFrame() == 4 || animationRunUp.getFrame() == 10)) {
					pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 6);
					pConsole->addCommand(commandPlaySound, "footstep_snow");
				}
			}
		} else{
			if (boundingBox.yv > 0) {
				animationWalkDown.run();
				animationWalkDown.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
				eyeVisible1 = true;
				eyeVisible2 = true;
				if (animationWalkDown.getChangedFrame() && (animationWalkDown.getFrame() == 0 || animationWalkDown.getFrame() == 4)) {
					pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 + 6);
					pConsole->addCommand(commandPlaySound, "footstep_snow");
				}
			}
			else if (boundingBox.yv < 0) {
				animationWalkUp.run();
				animationWalkUp.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
				if (animationWalkUp.getChangedFrame() && (animationWalkUp.getFrame() == 1 || animationWalkUp.getFrame() == 5)) {
					pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 6);
					pConsole->addCommand(commandPlaySound, "footstep_snow");
				}
			}
		}
	}
	if (eyeVisible1) {
		pSpriteCollection->drawLightSource(eyePosition1, glm::vec3(160, 214, 255), 1, 1, false);
		
	}
	pSpriteCollection->drawLightSource(eyePosition1, glm::vec3(160, 214, 255), 0.03, 0, false);
	pSpriteCollection->drawLightSource(eyePosition2, glm::vec3(160, 214, 255), 0.03, 0, false);
	if (eyeVisible2) {
		pSpriteCollection->drawLightSource(eyePosition2, glm::vec3(160, 214, 255), 1, 1, false);
		
	}
	//miniAnimation.run();
	//miniAnimation.draw(boundingBox.x-100, boundingBox.y-100, boundingBox.y + boundingBox.h);
}
