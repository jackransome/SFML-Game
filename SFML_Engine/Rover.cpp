#include "Rover.h"

Rover::Rover(InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, float _x, float _y) :
	Object(x, y, 24, 24, 0, controllable, true),
	Living(100, 2, factionFriendly),
	Pickuper(),
	Controllable(200),
	Miner() {
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	pSoundPlayer = _pSoundPlayer;
	boundingBox.x = _x;
	boundingBox.y = _y;
	spriteStackNormal = SpriteStack(pSpriteCollection, "rover_stack_1", 14, 20, 13, 2);
	isMining = false;
	type = objectRover;
	isLiving = true;
}

Rover::~Rover(){
	if (mineSoundPlaying) {
		pSoundPlayer->stopSound(mineSoundId);
	}
	if (moveSoundPlaying) {
		pSoundPlayer->stopSound(moveSoundId);
	}
}

void Rover::update() {
	//boundingBox.x = position.x*100;
	//boundingBox.y = position.y*100;
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	if (controlled) {
		if (pInputManager->isKeyDown(a)) {
			direction -= 0.1;
		}
		if (pInputManager->isKeyDown(d)) {
			direction += 0.1;
		}
		if (pInputManager->isKeyDown(w)) {
			if (pInputManager->isKeyDown(s)) {
				speed /= 2;
			}
			else {
				if (speed < maxSpeed) {
					speed += 1;
				}
			}
		}
		else if (pInputManager->isKeyDown(s)) {
			if (speed > -maxSpeed) {
				speed -= 1;
			}
		}
		else {
			speed /= 2;
		}
		if (abs(speed) < 0.8) {
			speed = 0;
		}
		boundingBox.xv = -speed * sin(-direction);
		boundingBox.yv = -speed * cos(-direction);
		if (!pInputManager->getMenuMode()) {
			if (pInputManager->onKeyDown(e)) {
				if (holding) {
					pConsole->addCommand(commandDrop, id);
					pSoundPlayer->playSoundByName("drop", 0.4);
				}
				else {
					pConsole->addCommand(commandPickUp, id);
				}
			}
			if (pInputManager->isKeyDown(e)) {
				isMining = true;
				if (!mineSoundPlaying) {
					mineSoundId = pSoundPlayer->playSoundByName("rover_mine_1", 0.1);
					pSoundPlayer->loopSoundBetween(mineSoundId, 1, 2);
					mineSoundPlaying = true;
				}

			}
			else {
				if (mineSoundPlaying) {
					pSoundPlayer->stopSound(mineSoundId);
				}
				isMining = false;
				mineSoundPlaying = false;
			}
		}
		else {
			if (mineSoundPlaying) {
				pSoundPlayer->stopSound(mineSoundId);
			}
			isMining = false;
			mineSoundPlaying = false;
		}

	}
	else {
		if (mineSoundPlaying) {
			pSoundPlayer->stopSound(mineSoundId);
		}
		isMining = false;
		mineSoundPlaying = false;
	}
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
	minePoint = glm::vec2(boundingBox.x + boundingBox.w / 2 - 30 * sin(-direction), boundingBox.y + boundingBox.h / 2 - 30 * cos(-direction));
	setPickupPos(minePoint);
	if (trackTimer < 5) {
		trackTimer++;
	}
	if ((boundingBox.yv != 0 || boundingBox.xv != 0) ) {
		if (!moveSoundPlaying) {
			moveSoundId = pSoundPlayer->playSoundByName("rover_move_1", 0.12);
			pSoundPlayer->loopSoundBetween(moveSoundId, 1, 2);
			
			moveSoundPlaying = true;
		}
		pConsole->addCommand(commandShakeScreen, 0.2f);
		if (trackTimer == 5) {
			pConsole->addCommand(commandAddObject, objectRoverTracks, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2, (direction / (2 * 3.1415)) * 360);
			trackTimer = 0;
		}
	}
	else if (moveSoundPlaying) {
		pSoundPlayer->stopSound(moveSoundId);
		moveSoundPlaying = false;
	}
	if (holding && !lastHolding) {
		pSoundPlayer->playSoundByName("pickup", 0.4);
	}
	lastHolding = holding;
	dropRotation = (direction / (2 * 3.1415)) * 360;
}

void Rover::draw(){
	//5,11 offset for the light
	glm::vec2 lightPos = getCenter() + glm::vec2(5 * cos(direction) - 11 * sin(direction), 5 * sin(direction) + 11 * cos(direction) - 26);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(160, 214, 255), 2, 2);
	spriteStackNormal.draw(boundingBox.x + boundingBox.w / 2 - 14, boundingBox.y + boundingBox.h / 2 - 20, boundingBox.y, (direction / (2 * 3.1415)) * 360, "bloom");
}

void Rover::onDeath() {
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x - 8, getCenter().y - 8);
	pConsole->addCommand(commandAddObject, objectExplosion, getCenter().x, getCenter().y, 15 + rand() % 10);
}
	
	
