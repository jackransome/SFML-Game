#include "ControlSwitcher.h"

ControlSwitcher::ControlSwitcher(ObjectCollection* _pObjectCollection, Console* _pConsole, SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Camera* _pCamera){
	pObjectCollection = _pObjectCollection;
	pConsole = _pConsole;
	pSpriteCollection = _pSpriteCollection;
	pInputManager = _pInputManager;
	pCamera = _pCamera;
}

void ControlSwitcher::setCurrentControlled(int ID){
	currentID = ID;
	controlling = true;
}

void ControlSwitcher::handleInput()
{
	if (active) {
		if (pInputManager->onKeyUp(mouseM)) {
			switchControl();
		}
	}
	if (pInputManager->isKeyDown(mouseM)) {
		active = true;
	}
	else {
		active = false;
	}

}

void ControlSwitcher::draw(){
	if (active) {
		glm::vec2 prosPos = pCamera->transformPosition(pObjectCollection->getClosestControllablePosition(currentID));
		glm::vec2 curPos = pCamera->transformPosition(pConsole->getControlPosition());
		pSpriteCollection->setAbsoluteMode(true);
		pSpriteCollection->addImageDraw(pSpriteCollection->getPointerFromName("switcher_overlay_current"), curPos.x - 10, curPos.y - 10, 1000000, 10, 10);
		pSpriteCollection->addImageDraw(pSpriteCollection->getPointerFromName("switcher_overlay_prospect"), prosPos.x - 10, prosPos.y - 10, 1000000, 10, 10);
		pSpriteCollection->setAbsoluteMode(false);
	}
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

