#include "MainCharacter.h"

#include <glm/gtx/vector_angle.hpp>

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

	animationRunLeftNa = SpriteSheet(pSpriteCollection, "mc_run_left_na", 22, 32, 6, 2);
	animationRunLeftNa.setChangeTimer(3);
	animationRunRightNa = SpriteSheet(pSpriteCollection, "mc_run_right_na", 22, 32, 6, 2);
	animationRunRightNa.setChangeTimer(3);
	animationRunDownNa = SpriteSheet(pSpriteCollection, "mc_run_down_na", 16, 32, 12, 2);
	animationRunDownNa.setChangeTimer(3);
	animationRunUpNa = SpriteSheet(pSpriteCollection, "mc_run_up_na", 16, 32, 12, 2);
	animationRunUpNa.setChangeTimer(3);
	animationWalkLeftNa = SpriteSheet(pSpriteCollection, "mc_walk_left_na", 16, 32, 4, 2);
	animationWalkLeftNa.setChangeTimer(4);
	animationWalkRightNa = SpriteSheet(pSpriteCollection, "mc_walk_right_na", 16, 32, 4, 2);
	animationWalkRightNa.setChangeTimer(4);
	animationWalkDownNa = SpriteSheet(pSpriteCollection, "mc_walk_front_na", 16, 32, 8, 2);
	animationWalkDownNa.setChangeTimer(4);
	animationWalkUpNa = SpriteSheet(pSpriteCollection, "mc_walk_back_na", 16, 32, 8, 2);
	animationWalkUpNa.setChangeTimer(4);
	animationBlinkNa = SpriteSheet(pSpriteCollection, "mc_blink_1_na", 16, 32, 1, 2);
	imageStandBackNa = SpriteSheet(pSpriteCollection, "mc_stand_back_na", 16, 32, 1, 2);
	imageStandLeftNa = SpriteSheet(pSpriteCollection, "mc_stand_left_na", 16, 32, 1, 2);
	imageStandRightNa = SpriteSheet(pSpriteCollection, "mc_stand_right_na", 16, 32, 1, 2);
	arm = pSpriteCollection->getPointerFromName("mc_arm");
	elbow = pSpriteCollection->getPointerFromName("mc_elbow");

	direction = down;
	isLiving = true;
	type = objectMainCharacter;
	faction = 0;
	setBuilt();	

	hasInventory = true;
	inventory = new Inventory(12, 64, true, false);
	hasToolbar = true;
	toolbar = new Inventory(3, 3, true, true);
}

void MainCharacter::onDeath() {
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 10 + rand() % 10);
}

void MainCharacter::update() {
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

double angleBetweenVectors360(const glm::vec2& vec1, const glm::vec2& vec2) {
	// Normalize the vectors
	glm::vec2 normVec1 = glm::normalize(vec1);
	glm::vec2 normVec2 = glm::normalize(vec2);

	// Calculate the angle in radians
	double angleRadians = glm::orientedAngle(normVec1, normVec2);

	// Convert the angle to degrees
	double angleDegrees = glm::degrees(angleRadians);

	// Ensure the angle is in the range [0, 360)
	if (angleDegrees < 0) {
		angleDegrees += 360.0;
	}

	return angleDegrees;
}

void MainCharacter::draw() {
	eyeVisible1 = false;
	eyeVisible2 = false;
	drawPowerConections();
	if (!usingArms) {
		if (sprinting) {
			if (boundingBox.xv < 0) {
				animationRunLeft.run();
				animationRunLeft.draw(boundingBox.x - 8 - 6, boundingBox.y - 48, boundingBox.y + boundingBox.h);
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
			}
			else if (boundingBox.xv > 0) {
				animationRunRight.run();
				animationRunRight.draw(boundingBox.x - 8 - 6, boundingBox.y - 48, boundingBox.y + boundingBox.h);
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
			}
		}
		if (boundingBox.xv == 0) {
			if (boundingBox.yv == 0) {
				switch (direction) {
				case up:
					imageStandBack.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
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
				}
			}
			else {
				if (boundingBox.yv > 0) {
					animationWalkDown.run();
					animationWalkDown.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
					shoulderPos1 = glm::vec2(boundingBox.x - 8 + 7, boundingBox.y - 48 + 25);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 + 25, boundingBox.y - 48 + 25);
					eyeVisible1 = true;
					eyeVisible2 = true;
				}
				else if (boundingBox.yv < 0) {
					animationWalkUp.run();
					animationWalkUp.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
					shoulderPos1 = glm::vec2(boundingBox.x - 8 + 7, boundingBox.y - 48 + 25);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 + 25, boundingBox.y - 48 + 25);
				}
			}
		}
	}
	else { //draw no arms version when arms are actually used
		if (sprinting) {
			if (boundingBox.xv < 0) {
				animationRunLeftNa.run();
				animationRunLeftNa.draw(boundingBox.x - 8 - 6, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				if (animationRunLeftNa.getFrame() == 0 || animationRunLeftNa.getFrame() == 3) {
					eyePosition1 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 19);
					eyePosition2 = glm::vec2(boundingBox.x - 8 - 6 + 5, boundingBox.y - 48 + 19);
					shoulderPos1 = glm::vec2(boundingBox.x - 8 - 6 + 18, boundingBox.y - 48 + 24);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 - 6 + 18, boundingBox.y - 48 + 24);

				}
				else if (animationRunLeftNa.getFrame() == 1 || animationRunLeftNa.getFrame() == 2) {
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
			}
			else if (boundingBox.xv > 0) {
				animationRunRightNa.run();
				animationRunRightNa.draw(boundingBox.x - 8 - 6, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				if (animationRunRightNa.getFrame() == 0 || animationRunRightNa.getFrame() == 3) {
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 33, boundingBox.y - 48 + 19);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 33, boundingBox.y - 48 + 19); //26 24
					shoulderPos1 = glm::vec2(boundingBox.x - 8 - 6 + 26, boundingBox.y - 48 + 24);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 - 6 + 26, boundingBox.y - 48 + 24);
				}
				else if (animationRunRightNa.getFrame() == 1 || animationRunRightNa.getFrame() == 2) {
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
			}
		}
		else {
			if (boundingBox.xv < 0) {
				animationWalkLeftNa.run();
				animationWalkLeftNa.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				if (animationWalkLeftNa.getFrame() == 0 || animationWalkLeftNa.getFrame() == 2) {
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 13);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 9, boundingBox.y - 48 + 13);
					shoulderPos1 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 23);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 23);
				}
				else if (animationWalkLeftNa.getFrame() == 1) {
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
			}
			else if (boundingBox.xv > 0) {
				animationWalkRightNa.run();
				animationWalkRightNa.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
				if (animationWalkRightNa.getFrame() == 0 || animationWalkRightNa.getFrame() == 2) {
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 13);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 13);
					shoulderPos1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 23);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 23);
				}
				else if (animationWalkRightNa.getFrame() == 1) {
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
			}
		}
		if (boundingBox.xv == 0) {
			if (boundingBox.yv == 0) {
				switch (direction) {
				case up:
					imageStandBackNa.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
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
						animationBlinkNa.drawFrame(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h, 1);
					}
					else {
						animationBlinkNa.drawFrame(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h, 0);
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
					imageStandLeftNa.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
					break;
				case right:
					eyeVisible1 = true;
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 13);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 23, boundingBox.y - 48 + 13);
					shoulderPos1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 23);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 23);
					//15 23
					imageStandRightNa.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
					break;

				}
			}
			if (sprinting) {
				if (boundingBox.yv > 0) {
					animationRunDownNa.run();
					animationRunDownNa.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
					if ((animationRunDownNa.getFrame() > 0 && animationRunDownNa.getFrame() < 4) || (animationRunDownNa.getFrame() > 6 && animationRunDownNa.getFrame() < 10)) {
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
				}
				else if (boundingBox.yv < 0) {
					animationRunUpNa.run();
					animationRunUpNa.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
					if ((animationRunUpNa.getFrame() > 0 && animationRunUpNa.getFrame() < 4) || (animationRunUpNa.getFrame() > 6 && animationRunUpNa.getFrame() < 10)) {
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
				}
			}
			else {
				if (boundingBox.yv > 0) {
					animationWalkDownNa.run();
					animationWalkDownNa.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
					shoulderPos1 = glm::vec2(boundingBox.x - 8 + 7, boundingBox.y - 48 + 25);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 + 25, boundingBox.y - 48 + 25);
					eyeVisible1 = true;
					eyeVisible2 = true;
				}
				else if (boundingBox.yv < 0) {
					animationWalkUpNa.run();
					animationWalkUpNa.draw(boundingBox.x - 8, boundingBox.y - 48, boundingBox.y + boundingBox.h);
					eyePosition1 = glm::vec2(boundingBox.x - 8 + 13, boundingBox.y - 48 + 13);
					eyePosition2 = glm::vec2(boundingBox.x - 8 + 19, boundingBox.y - 48 + 13);
					shoulderPos1 = glm::vec2(boundingBox.x - 8 + 7, boundingBox.y - 48 + 25);
					shoulderPos2 = glm::vec2(boundingBox.x - 8 + 25, boundingBox.y - 48 + 25);
				}
			}
		}
		//drawing arms:
		
		glm::vec2 mousePos = glm::vec2(pInputManager->translatedMouseX, pInputManager->translatedMouseY);
		glm::vec2 difference;
		switch (direction) {
		case up:
			aimCenter = (shoulderPos1 + shoulderPos2) / 2.0f;

			difference = mousePos - aimCenter;
			difference /= sqrt(difference.x * difference.x + difference.y * difference.y);
			if (difference.y > 0) {
				if (difference.x < 0) {
					difference = glm::vec2(-1, 0);
				}
				else {
					difference = glm::vec2(1, 0);
				}
			}
			holdPoint = aimCenter + holdRadius * difference;

			//left arm

			tempV1 = holdPoint - shoulderPos1;
			tempDistance = sqrt(tempV1.x * tempV1.x + tempV1.y * tempV1.y);
			tempV1 /= tempDistance;
			tempV2 = perpendicularClockwise(tempV1);
			tempA = acos((tempDistance / 2.0f) / armHalfLength);
			elbow1 = shoulderPos1 + (tempDistance / 2.0f) * tempV1 + tempV2 * armHalfLength * sin(tempA);

			//right arm

			tempV1 = holdPoint - shoulderPos2;
			tempDistance = sqrt(tempV1.x * tempV1.x + tempV1.y * tempV1.y);
			tempV1 /= tempDistance;
			tempV2 = perpendicularCounterClockwise(tempV1);
			tempA = acos((tempDistance / 2.0f) / armHalfLength);
			elbow2 = shoulderPos2 + (tempDistance / 2.0f) * tempV1 + tempV2 * armHalfLength * sin(tempA);
			


			break;
		case down:
			aimCenter = (shoulderPos1 + shoulderPos2) / 2.0f;

			difference = mousePos - aimCenter;
			difference /= sqrt(difference.x * difference.x + difference.y * difference.y);
			if (difference.y < 0) {
				if (difference.x < 0) {
					difference = glm::vec2(-1, 0);
				}
				else {
					difference = glm::vec2(1, 0);
				}
			}
			holdPoint = aimCenter + holdRadius * difference;
			
			//left arm

			tempV1 = holdPoint - shoulderPos1;
			tempDistance = sqrt(tempV1.x * tempV1.x + tempV1.y * tempV1.y);
			tempV1 /= tempDistance;
			
			tempV2 = perpendicularCounterClockwise(tempV1);
			
			tempA = acos((tempDistance / 2.0f) / armHalfLength);

			elbow1 = shoulderPos1 + (tempDistance / 2.0f) * tempV1+  tempV2* armHalfLength * sin(tempA);
			
			//right arm

			tempV1 = holdPoint - shoulderPos2;
			tempDistance = sqrt(tempV1.x * tempV1.x + tempV1.y * tempV1.y);
			tempV1 /= tempDistance;
			tempV2 = perpendicularClockwise(tempV1);
			tempA = acos((tempDistance / 2.0f) / armHalfLength);
			elbow2 = shoulderPos2 + (tempDistance / 2.0f) * tempV1 + tempV2 * armHalfLength * sin(tempA);


			break;
		case left:
			aimCenter.x = getCenter().x;
			aimCenter.y = shoulderPos1.y;

			difference = mousePos - aimCenter;
			difference /= sqrt(difference.x * difference.x + difference.y * difference.y);
			if (difference.x > 0) {
				if (difference.y < 0) {
					difference = glm::vec2(0, -1);
				}
				else {
					difference = glm::vec2(0, 1);
				}
			}
			holdPoint = aimCenter + holdRadius * difference;

			//left arm

			tempV1 = holdPoint - shoulderPos1;
			tempDistance = sqrt(tempV1.x * tempV1.x + tempV1.y * tempV1.y);
			tempV1 /= tempDistance;
			tempV2 = perpendicularClockwise(tempV1);
			tempA = acos((tempDistance / 2.0f) / armHalfLength);
			elbow1 = shoulderPos1 + (tempDistance / 2.0f) * tempV1 + tempV2 * armHalfLength * sin(tempA);

			//right arm

			tempV1 = holdPoint - shoulderPos2;
			tempDistance = sqrt(tempV1.x * tempV1.x + tempV1.y * tempV1.y);
			tempV1 /= tempDistance;
			tempV2 = perpendicularCounterClockwise(tempV1);
			tempA = acos((tempDistance / 2.0f) / armHalfLength);
			elbow2 = shoulderPos2 + (tempDistance / 2.0f) * tempV1 + tempV2 * armHalfLength * sin(tempA);

			break;
		case right:
			aimCenter.x = getCenter().x;
			aimCenter.y = shoulderPos1.y;

			difference = mousePos - aimCenter;
			difference /= sqrt(difference.x * difference.x + difference.y * difference.y);
			if (difference.x < 0) {
				if (difference.y < 0) {
					difference = glm::vec2(0, -1);
				}
				else {
					difference = glm::vec2(0, 1);
				}
			}
			holdPoint = aimCenter + holdRadius * difference;

			//left arm

			tempV1 = holdPoint - shoulderPos1;
			tempDistance = sqrt(tempV1.x * tempV1.x + tempV1.y * tempV1.y);
			tempV1 /= tempDistance;
			tempV2 = perpendicularClockwise(tempV1);
			tempA = acos((tempDistance / 2.0f) / armHalfLength);
			elbow1 = shoulderPos1 + (tempDistance / 2.0f) * tempV1 + tempV2 * armHalfLength * sin(tempA);

			//right arm

			tempV1 = holdPoint - shoulderPos2;
			tempDistance = sqrt(tempV1.x * tempV1.x + tempV1.y * tempV1.y);
			tempV1 /= tempDistance;
			tempV2 = perpendicularCounterClockwise(tempV1);
			tempA = acos((tempDistance / 2.0f) / armHalfLength);
			elbow2 = shoulderPos2 + (tempDistance / 2.0f) * tempV1 + tempV2 * armHalfLength * sin(tempA);

			break;
		}
		float offset = 1;
		if (direction == down || direction == left) {
			offset = 1;
		}
		else {
			offset = -1;
		}
		r = angleBetweenVectors360(glm::vec2(1, 0), elbow1 - shoulderPos1);
		pSpriteCollection->addRotatedImageDrawCut(arm, shoulderPos1.x - 10, shoulderPos1.y-2, boundingBox.y + boundingBox.h + offset, 0, 0, 10, 2, 2, r);
		r = angleBetweenVectors360(glm::vec2(1, 0), holdPoint - elbow1);
		pSpriteCollection->addRotatedImageDrawCut(arm, elbow1.x - 10, elbow1.y-2, boundingBox.y + boundingBox.h + offset, 0, 0, 10, 2, 2, r);
		pSpriteCollection->addImageDraw(elbow, elbow1.x-2, elbow1.y-2, boundingBox.y + boundingBox.h + offset, 4, 4);
		if (direction == down || direction == right) {
			offset = 1;
		}
		else {
			offset = -1;
		}
		r = angleBetweenVectors360(glm::vec2(1, 0), elbow2 - shoulderPos2);
		pSpriteCollection->addRotatedImageDrawCut(arm, shoulderPos2.x - 10, shoulderPos2.y - 2, boundingBox.y + boundingBox.h + offset, 0, 0, 10, 2, 2, r);
		r = angleBetweenVectors360(glm::vec2(1, 0), holdPoint - elbow2);
		pSpriteCollection->addRotatedImageDrawCut(arm, elbow2.x - 10, elbow2.y - 2, boundingBox.y + boundingBox.h + offset, 0, 0, 10, 2, 2, r);

		pSpriteCollection->addImageDraw(elbow, elbow2.x-2, elbow2.y-2, boundingBox.y + boundingBox.h + offset, 4, 4);
		//pSpriteCollection->addRotatedImageDraw(arm, shoulderPos1.x - 2, shoulderPos1.y, boundingBox.y + boundingBox.h, 2, r, 9, 3);
		//pSpriteCollection->addRotatedImageDraw(arm, shoulderPos2.x - 2, shoulderPos2.y, boundingBox.y + boundingBox.h, 2, 1, 1, 2, 2, 9, 3);
	}
	if (eyeVisible1) {
		pSpriteCollection->drawLightSource(eyePosition1, glm::vec3(160, 214, 255), 1*getPercentage(), 1);
		
	}
	pSpriteCollection->drawLightSource(eyePosition1, glm::vec3(160, 214, 255), 0.03, 0);
	pSpriteCollection->drawLightSource(eyePosition2, glm::vec3(160, 214, 255), 0.03, 0);

	//pSpriteCollection->drawLightSource(shoulderPos1, glm::vec3(255, 214, 55), 0.06, 1);
	//pSpriteCollection->drawLightSource(shoulderPos2, glm::vec3(255, 214, 55), 0.06, 1);

	//pSpriteCollection->drawLightSource(holdPoint, glm::vec3(255, 214, 55), 0.06, 1);
	//pSpriteCollection->drawLightSource(elbow1, glm::vec3(255, 214, 55), 0.06, 1);
	//std::cout << "x: " << elbow1.x << ", y: " << elbow1.y << "\n";
	//pSpriteCollection->drawLightSource(elbow2, glm::vec3(255, 214, 55), 0.06, 1);

	if (eyeVisible2) {
		pSpriteCollection->drawLightSource(eyePosition2, glm::vec3(160, 214, 255), 1 * getPercentage(), 1);
	}



	boundingBox.xv = 0;
	boundingBox.yv = 0;
}

glm::vec2 MainCharacter::perpendicularClockwise(const glm::vec2& v) {
	return glm::vec2(v.y, -v.x);
}

glm::vec2 MainCharacter::perpendicularCounterClockwise(const glm::vec2& v) {
	return glm::vec2(-v.y, v.x);
}