#include "PowerManager.h"

PowerManager::PowerManager(SpriteCollection* _pSpriteCollection, Console* _pConsole, InputManager* _pInputManager, ObjectCollection* _pObjectCollection, Camera* _pCamera){
	pSpriteCollection = _pSpriteCollection;
	pConsole = _pConsole;
	pInputManager = _pInputManager;
	pObjectCollection = _pObjectCollection;
	pCamera = _pCamera;
}

void PowerManager::activate(){
	active = true;
}

void PowerManager::toggleActive(){
	if (active) {
		cancel();
	}
	else {
		active = true;
	}
}

bool PowerManager::isActive() {
	return active;
}

void PowerManager::cancel(){
	active = false;
	from = std::shared_ptr<Object>();
	to = std::shared_ptr<Object>();
}

void PowerManager::update(){
	if (active) {
		if (pInputManager->onKeyDown(mouseR) || pInputManager->onKeyDown(mouseM)) {
			cancel();
			return;
		}
		std::shared_ptr<Object> object;
		if (object = pObjectCollection->getClosestPowerNode()) {
			if (pInputManager->onKeyUp(mouseL)) {
				auto sharedTarget = from.lock();
				if (!sharedTarget) {
					from = object;
				}
				else {
					if (sharedTarget->getId() == to->getId()) {
						cancel();
						return;
					}
					else {
						//CONNECT POWER
						std::dynamic_pointer_cast<PowerNode>(sharedTarget)->addConnection(std::dynamic_pointer_cast<PowerNode>(object).get());
						std::dynamic_pointer_cast<PowerNode>(object)->addConnection(std::dynamic_pointer_cast<PowerNode>(sharedTarget).get());
						cancel();
						active = true;
					}
				}
			}
			else {
				to = object;
			}
		}
		else {
			active = false;
		}
		pInputManager->disableMouseButtons();
	}
}

void PowerManager::draw(){
	float scale = pSpriteCollection->getScale();
	pSpriteCollection->setAbsoluteMode(true);
	glm::vec2 position;
	if (auto sharedTarget = from.lock()) {
		position = pCamera->transformPosition(sharedTarget->getCenter() - glm::vec2(11,11));
		pSpriteCollection->addRotatedImageDraw(pSpriteCollection->getPointerFromName("power_manager_overlay_1"), position.x, position.y, 1000000, scale, 0, 22, 22);
	}
	if (to) {
		position = pCamera->transformPosition(to->getCenter() - glm::vec2(11, 11));
		pSpriteCollection->addRotatedImageDraw(pSpriteCollection->getPointerFromName("power_manager_overlay_2"), position.x, position.y, 1000000, scale, 0, 22, 22);
	}
	pSpriteCollection->setAbsoluteMode(false);
}
