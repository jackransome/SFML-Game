#include "ControlSwitcher.h"

ControlSwitcher::ControlSwitcher(ObjectCollection* _pObjectCollection, Console* _pConsole, SpriteCollection* _pSpriteCollection){
	pObjectCollection = _pObjectCollection;
	pConsole = _pConsole;
	pSpriteCollection = _pSpriteCollection;
}

void ControlSwitcher::drawOverlay(){
	if (!controlling) { return; }
	prospectiveID = pObjectCollection->getClosestControllable(currentID);
	glm::vec2 temp;
	if (prospectiveID != -1) {
		//draw on prospective object
		temp = pObjectCollection->getObjectById(prospectiveID)->getCenter();
		pSpriteCollection->addCircleDraw(temp.x, temp.y, 5, 10000, sf::Color(100, 255, 100, 100));
	}

	//draw on current object
	temp = pObjectCollection->getObjectById(currentID)->getCenter();
	pSpriteCollection->addCircleDraw(temp.x, temp.y, 5, 1000000, sf::Color(100, 255, 100, 100));
	int range = dynamic_cast<Controllable*>(pObjectCollection->getObjectById(currentID))->getRange();
	pSpriteCollection->addCircleDraw(temp.x - range, temp.y - range, range, 1000000, sf::Color(100, 100, 255, 20));
}

void ControlSwitcher::setCurrentControlled(int ID){
	currentID = ID;
	controlling = true;
}

void ControlSwitcher::switchControl(){
	prospectiveID = pObjectCollection->getClosestControllable(currentID);
	if (prospectiveID >= 0) {
		pConsole->addCommand(commandSetCameraFocusId, prospectiveID);
		pConsole->addCommand(commandEnableObjectControls, prospectiveID);
		currentID = prospectiveID;
		pConsole->addCommand(commandPlaySound, "transfer", 0.05);
		pConsole->addCommand(commandShakeScreen, 10.0f);
		pConsole->addCommand(commandBlink);
	}
	else {
		std::cout << "Prospective ID is -1\n";
	}
}

glm::vec2 ControlSwitcher::getControlPosition(){
	return pObjectCollection->getObjectById(currentID)->getCenter();
}

bool ControlSwitcher::getControlling(){
	return controlling;
}

void ControlSwitcher::setControlling(bool _controlling){
	controlling = _controlling;
}

