#include "ControlSwitcher.h"

ControlSwitcher::ControlSwitcher(ObjectCollection* _pObjectCollection, Console* _pConsole, SpriteCollection* _pSpriteCollection){
	pObjectCollection = _pObjectCollection;
	pConsole = _pConsole;
	pSpriteCollection = _pSpriteCollection;
}

void ControlSwitcher::drawOverlay(){
	prospectiveID = pObjectCollection->getClosestControllable(currentID);
	glm::vec2 temp;
	if (prospectiveID != -1) {
		//draw on prospective object
		temp = pObjectCollection->getObjectById(prospectiveID)->getCenter();
		pSpriteCollection->addCircleDraw(temp.x, temp.y, 5, 10000, sf::Color(100, 255, 100, 100));
	}

	//draw on current object
	temp = pObjectCollection->getObjectById(currentID)->getCenter();
	pSpriteCollection->addCircleDraw(temp.x, temp.y, 5, 10000, sf::Color(100, 255, 100, 100));
}

void ControlSwitcher::setCurrentControlled(int ID){
	currentID = ID;
}

void ControlSwitcher::switchControl(){
	prospectiveID = pObjectCollection->getClosestControllable(currentID);
	if (prospectiveID >= 0) {
		pConsole->addCommand(commandSetCameraFocusId, prospectiveID);
		pConsole->addCommand(commandEnableObjectControls, prospectiveID);
		currentID = prospectiveID;
	}
	else {
		std::cout << "Prospective ID is -1\n";
	}
}

