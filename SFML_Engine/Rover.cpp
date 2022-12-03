#include "Rover.h"

Rover::Rover(InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, float _x, float _y) :
	Object(x, y, 24, 24, 0, movable, true),
	Living(100, 2),
	Pickuper(),
	Controllable(200) {
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	pSoundPlayer = _pSoundPlayer;
	boundingBox.x = _x;
	boundingBox.y = _y;
	spriteStackCrate = SpriteStack(pSpriteCollection, "rover_stack_crate", 14, 30, 10, 2);
	spriteStackRelay = SpriteStack(pSpriteCollection, "rover_stack_relay", 14, 33, 35, 2);
	spriteStackNormal = SpriteStack(pSpriteCollection, "rover_stack_1", 14, 20, 13, 2);
}

void Rover::update(){
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
			boundingBox.xv = -speed * sin(-direction);
			boundingBox.yv = -speed * cos(-direction);
		}
		if (pInputManager->isKeyDown(s)) {
			boundingBox.xv = speed * sin(-direction);
			boundingBox.yv = speed * cos(-direction);
		}
		if (pInputManager->onKeyDown(e)) {
			if (holding) {
				pConsole->addCommand(commandDrop, id);
				pSoundPlayer->playSoundByName("drop", 0.2);
			}
			else {
				pConsole->addCommand(commandPickUp, id);
			}
		}
	}
	
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
	setPickupPos(glm::vec2(boundingBox.x + boundingBox.w / 2 - 30 * sin(-direction), boundingBox.y + boundingBox.h / 2 - 30 * cos(-direction)));
	if (trackTimer < 5) {
		trackTimer++;
	}
	if ((boundingBox.yv != 0 || boundingBox.xv != 0) ) {
		if (!soundPlaying) {
			soundId = pSoundPlayer->playSoundByName("rover_move_1", 0.045);
			pSoundPlayer->loopSoundBetween(soundId, 1, 2);
			
			soundPlaying = true;
		}
		pConsole->addCommand(commandShakeScreen, 0.2f);
		if (trackTimer == 5) {
			pConsole->addCommand(commandAddObject, objectRoverTracks, boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2, (direction / (2 * 3.1415)) * 360);
			trackTimer = 0;
		}
	}
	else if (soundPlaying) {
		pSoundPlayer->stopSound(soundId);
		soundPlaying = false;
	}
	if (holding && !lastHolding) {
		pSoundPlayer->playSoundByName("pickup", 0.2);
	}
	lastHolding = holding;
	dropRotation = (direction / (2 * 3.1415)) * 360;
}

void Rover::draw(){
	//5,11 offset for the light
	glm::vec2 lightPos = getCenter() + glm::vec2(5 * cos(direction) - 11 * sin(direction), 5 * sin(direction) + 11 * cos(direction) - 26);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(160, 214, 255), 2, 1, false);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(160, 214, 255), 0.2, 0, false);
	//pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + boundingBox.w / 2 - 30 * sin(-direction), boundingBox.y + boundingBox.h / 2 - 30 * cos(-direction)), glm::vec3(0, 255, 0), 2, 1, false);
	/*if (holding) {
		if (typeHeld == objectCrate) {
			spriteStackCrate.draw(boundingBox.x + boundingBox.w / 2 - 14, boundingBox.y + boundingBox.h / 2 - 40, 6, (direction / (2 * 3.1415)) * 360, 14, 40);
		}
		else if (typeHeld == objectRelay) {
			spriteStackRelay.draw(boundingBox.x + boundingBox.w / 2 - 14, boundingBox.y + boundingBox.h / 2 - 46, 6, (direction / (2 * 3.1415)) * 360, 14, 46);
		}
		
	}
	else {*/
		spriteStackNormal.draw(boundingBox.x + boundingBox.w / 2 - 14, boundingBox.y + boundingBox.h / 2 - 20, 6, (direction / (2 * 3.1415)) * 360);
	//}
}
	
	
