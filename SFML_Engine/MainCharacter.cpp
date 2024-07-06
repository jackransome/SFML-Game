#include "MainCharacter.h"

MainCharacter::MainCharacter(InputManager* _pInputManager, SpriteCollection *_pSpriteCollection, Console *_pConsole, float _x, float _y) :
	Object(_x, _y, 16, 16, 0, controllable, true),
	Living(100, 2, &isLiving),
	Controllable(200, &isControllable),
	PowerNode(_pConsole, 10,0, &isPowerNode, false, false, 2, _pSpriteCollection, _x, _y, &id) {
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
	isLiving = true;
	type = objectMainCharacter;

	miniAnimation = SpriteSheet(pSpriteCollection, "mc_mini_run_right", 8, 20, 2, 2);
	miniAnimation.setChangeTimer(12);
	faction = 0;
	setBuilt();	
}

void MainCharacter::onDeath() {
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 10 + rand() % 10);
}

void MainCharacter::update() {
	//boundingBox.x = 100*position.x;
	//boundingBox.y = 100*position.y;
	updatePowerPosition(getCenter().x, getCenter().y);
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	if (controlled && getPercentage() > 0) {
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
		if ((getHealth() / getMaxHealth()) < ((double)rand() / (RAND_MAX)) && ((double)rand() / (RAND_MAX)) > 0.85) {
			if (((double)rand() / (RAND_MAX)) > 0.7) {
				pConsole->addCommand(commandAddObject, objectSpark, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 5.0, 1.0);
			}
			else {
				pConsole->addCommand(commandAddObject, objectSmoke, boundingBox.x + boundingBox.w * ((double)rand() / (RAND_MAX)), boundingBox.y + boundingBox.h * ((double)rand() / (RAND_MAX)), 1.0, 1.0);
			}
		}
	}
	
	//pConsole->addCommand(commandSetCameraPos, boundingBox.x, boundingBox.y);
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;

	//physicsBody->SetTransform(b2Vec2(boundingBox.x / 100, boundingBox.y/100), 0);
	//physicsBody->SetLinearVelocity(b2Vec2(boundingBox.xv / 100, boundingBox.yv / 100));
	if ((boundingBox.xv || boundingBox.yv)) {
		discharge(0.01);
	}

	if (sprinting) {
		if (boundingBox.xv < 0) {
			if (animationRunLeft.getChangedFrame() && animationRunLeft.getFrame() == 1) {
				pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2 - 10, boundingBox.y + boundingBox.h / 2 + 6);
				pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
			}
		}
		else if (boundingBox.xv > 0) {

			if (animationRunRight.getChangedFrame() && animationRunRight.getFrame() == 1) {
				pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2 + 10, boundingBox.y + boundingBox.h / 2 + 6);
				pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
			}
		}
	}
	else {
		if (boundingBox.xv < 0) {
			if (animationWalkLeft.getChangedFrame() && animationWalkLeft.getFrame() == 1) {
				pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2 - 6, boundingBox.y + boundingBox.h / 2 + 6);
				pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
			}
		}
		else if (boundingBox.xv > 0) {

			if (animationWalkRight.getChangedFrame() && animationWalkRight.getFrame() == 1) {
				pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2 + 6, boundingBox.y + boundingBox.h / 2 + 6);
				pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
			}
		}
	}
	if (boundingBox.xv == 0) {
		if (sprinting) {
			if (boundingBox.yv > 0) {
				if (animationRunDown.getChangedFrame() && (animationRunDown.getFrame() == 0 || animationRunDown.getFrame() == 6)) {
					pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 + 6);
					pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
				}
			}
			else if (boundingBox.yv < 0) {
				if (animationRunUp.getChangedFrame() && (animationRunUp.getFrame() == 4 || animationRunUp.getFrame() == 10)) {
					pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 6);
					pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
				}
			}
		}
		else {
			if (boundingBox.yv > 0) {
				if (animationWalkDown.getChangedFrame() && (animationWalkDown.getFrame() == 0 || animationWalkDown.getFrame() == 4)) {
					pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 + 6);
					pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
				}
			}
			else if (boundingBox.yv < 0) {
				if (animationWalkUp.getChangedFrame() && (animationWalkUp.getFrame() == 1 || animationWalkUp.getFrame() == 5)) {
					pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 6);
					pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
				}
			}
		}
	}
}

void MainCharacter::draw() {
	eyeVisible1 = false;
	eyeVisible2 = false;
	drawPowerConections();
	if (sprinting) {
		if (boundingBox.xv < 0) {
			animationRunLeft.run();
			animationRunLeft.draw(boundingBox.x-8-6, boundingBox.y-48, boundingBox.y + boundingBox.h);
			if (animationRunLeft.getFrame() == 0 || animationRunLeft.getFrame() == 3) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 19);
				eyePosition2 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 19);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 - 6 + 18, boundingBox.y - 48 + 24);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 - 6 + 18, boundingBox.y - 48 + 24);

			}
			else if (animationRunLeft.getFrame() == 1 || animationRunLeft.getFrame() == 2) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 21);
				eyePosition2 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 21);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 - 6 + 18, boundingBox.y - 48 + 26);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 - 6 + 18, boundingBox.y - 48 + 26);
			}
			else {
				eyePosition1 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 17);
				eyePosition2 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 17);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 - 6 + 18, boundingBox.y - 48 + 22);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 - 6 + 18, boundingBox.y - 48 + 22);
			}
			eyeVisible1 = true;
			if (animationRunLeft.getChangedFrame() && animationRunLeft.getFrame() == 1) {
				//pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2 - 10, boundingBox.y + boundingBox.h / 2 + 6);
				//pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
			}
		}
		else if (boundingBox.xv > 0) {
			animationRunRight.run();
			animationRunRight.draw(boundingBox.x- 8-6, boundingBox.y - 48, boundingBox.y + boundingBox.h);
			if (animationRunRight.getFrame() == 0 || animationRunRight.getFrame() == 3) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 33, boundingBox.y - 48 + 19);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 33, boundingBox.y - 48 + 19); //26 24
				shoulderPos1 = glm::vec2(boundingBox.x - 8 - 6 + 26, boundingBox.y - 48 + 24);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 - 6 + 26, boundingBox.y - 48 + 24);
			}
			else if (animationRunRight.getFrame() == 1 || animationRunRight.getFrame() == 2) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 33, boundingBox.y - 48 + 21);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 33, boundingBox.y - 48 + 21);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 - 6 + 26, boundingBox.y - 48 + 26);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 - 6 + 26, boundingBox.y - 48 + 26);
			}
			else {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 33, boundingBox.y - 48 + 17);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 33, boundingBox.y - 48 + 17);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 - 6 + 26, boundingBox.y - 48 + 22);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 - 6 + 26, boundingBox.y - 48 + 22);
			}
			eyeVisible1 = true;
			if (animationRunRight.getChangedFrame() && animationRunRight.getFrame() == 1) {
				//pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2 + 10, boundingBox.y + boundingBox.h / 2 + 6);
				//pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
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
				shoulderPos1 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 23);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 23);
			}
			else if (animationWalkLeft.getFrame() == 1) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 15);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 15);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 25);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 25);
			}
			else {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 11);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 11);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 21);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 21);
			}
			eyeVisible1 = true;
			if (animationWalkLeft.getChangedFrame() && animationWalkLeft.getFrame() == 1) {
				//pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2 - 6, boundingBox.y + boundingBox.h / 2+6);
				//pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
			}
		}
		else if (boundingBox.xv > 0) {
			animationWalkRight.run();
			animationWalkRight.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
			if (animationWalkRight.getFrame() == 0 || animationWalkRight.getFrame() == 2) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 13);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 13);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 23);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 23);
			}
			else if (animationWalkRight.getFrame() == 1) {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 15);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 15);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 25);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 25);
			}
			else {
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 11);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 11);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 21);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 21);
			}
			eyeVisible1 = true;
			if (animationWalkRight.getChangedFrame() && animationWalkRight.getFrame() == 1) {
				//pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2 +6, boundingBox.y + boundingBox.h / 2 + 6);
				//pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
			}
		}
	}
	if (boundingBox.xv == 0) {
		if (boundingBox.yv == 0){
			switch (direction) {
			case up:
				imageStandBack.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y+ boundingBox.h);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 + 7, boundingBox.y - 48 + 25);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 + 25, boundingBox.y - 48 + 25);
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
				break;
			case down:
				blinkCounter++;
				if (blinkCounter == 173) {
					blinkCounter = 0;

				}
				shoulderPos1 = glm::vec2(boundingBox.x - 8 + 7, boundingBox.y - 48 + 25);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 + 25, boundingBox.y - 48 + 25);
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
				shoulderPos1 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 23);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 23);
				imageStandLeft.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				break;
			case right:
				eyeVisible1 = true;
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 13);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 13);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 23);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 23);
				//15 23
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
					shoulderPos1 = glm::vec2(boundingBox.x - 8 + 7, boundingBox.y - 48 + 27);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 + 25, boundingBox.y - 48 + 27);
				}
				else {
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
					shoulderPos1 = glm::vec2(boundingBox.x - 8 + 7, boundingBox.y - 48 + 25);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 + 25, boundingBox.y - 48 + 25);
				}

				eyeVisible1 = true;
				eyeVisible2 = true;
				if (animationRunDown.getChangedFrame() && (animationRunDown.getFrame() == 0 || animationRunDown.getFrame() == 6)) {
					//pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 + 6);
					//pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
				}
			}
			else if (boundingBox.yv < 0) {
				animationRunUp.run();
				animationRunUp.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				if ((animationRunUp.getFrame() > 0 && animationRunUp.getFrame() < 4) || (animationRunUp.getFrame() > 6 && animationRunUp.getFrame() < 10)) {
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 15);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 15);
					shoulderPos1 = glm::vec2(boundingBox.x - 8 + 7, boundingBox.y - 48 + 25);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 + 25, boundingBox.y - 48 + 25);
				}
				else {
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
					shoulderPos1 = glm::vec2(boundingBox.x - 8 + 7, boundingBox.y - 48 + 23);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 + 25, boundingBox.y - 48 + 23);
				}
				if (animationRunUp.getChangedFrame() && (animationRunUp.getFrame() == 4 || animationRunUp.getFrame() == 10)) {
					//pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 6);
					//pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
				}
			}
		} else{
			if (boundingBox.yv > 0) {
				animationWalkDown.run();
				animationWalkDown.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 + 7, boundingBox.y - 48 + 25);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 + 25, boundingBox.y - 48 + 25);
				eyeVisible1 = true;
				eyeVisible2 = true;
				if (animationWalkDown.getChangedFrame() && (animationWalkDown.getFrame() == 0 || animationWalkDown.getFrame() == 4)) {
					//pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 + 6);
					//pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
				}
			}
			else if (boundingBox.yv < 0) {
				animationWalkUp.run();
				animationWalkUp.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
				eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
				shoulderPos1 = glm::vec2(boundingBox.x - 8 + 7, boundingBox.y - 48 + 25);
				shoulderPos2 = glm::vec2(boundingBox.x - 8 + 25, boundingBox.y - 48 + 25);
				if (animationWalkUp.getChangedFrame() && (animationWalkUp.getFrame() == 1 || animationWalkUp.getFrame() == 5)) {
					//pConsole->addCommand(commandAddObject, objectFootprint, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 6);
					//pConsole->addCommand(commandPlaySound, "footstep_snow", 0.1);
				}
			}
		}
	}
	if (eyeVisible1) {
		pSpriteCollection->drawLightSource(eyePosition1, glm::vec3(160, 214, 255), 1*getPercentage(), 1);
		
	}
	pSpriteCollection->drawLightSource(eyePosition1, glm::vec3(160, 214, 255), 0.03, 0);
	pSpriteCollection->drawLightSource(eyePosition2, glm::vec3(160, 214, 255), 0.03, 0);

	pSpriteCollection->drawLightSource(shoulderPos1, glm::vec3(255, 214, 55), 0.06, 1);
	pSpriteCollection->drawLightSource(shoulderPos2, glm::vec3(255, 214, 55), 0.06, 1);

	if (eyeVisible2) {
		pSpriteCollection->drawLightSource(eyePosition2, glm::vec3(160, 214, 255), 1 * getPercentage(), 1);
	}

	//drawing arms:
	switch (direction) {
	case up:
		break;
	case down:
		break;
	case left:
		break;
	case right:
		break;
	}

	boundingBox.xv = 0;
	boundingBox.yv = 0;
}
