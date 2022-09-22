#include "Rover.h"

Rover::Rover(InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, float _x, float _y) :
	Object(x, y, 16, 16, 0, movable, true),
	Living(100, 2) {
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	boundingBox.x = _x;
	boundingBox.y = _y;
	spriteStackCrate = SpriteStack(pSpriteCollection, "rover_stack_crate", 14, 30, 10, 2);
	spriteStackNormal = SpriteStack(pSpriteCollection, "rover_stack_1", 14, 20, 10, 2);
	
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
		if (pInputManager->onKeyDown(n8)) {
			hasCrate = !hasCrate;
		}
	}
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}

void Rover::draw(){
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 20), glm::vec3(160, 214, 255), 2, 1, false);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 20), glm::vec3(160, 214, 255), 0.2, 0, false);
	if (hasCrate) {
		spriteStackCrate.draw(boundingBox.x + boundingBox.w / 2 - 14, boundingBox.y + boundingBox.h / 2 - 30, 6, (direction / (2 * 3.1415)) * 360, 14, 40);
	}
	else {
		spriteStackNormal.draw(boundingBox.x + boundingBox.w / 2 - 14, boundingBox.y + boundingBox.h / 2 - 20, 6, (direction / (2 * 3.1415)) * 360);
	}
}
	
	
