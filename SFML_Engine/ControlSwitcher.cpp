#include "ControlSwitcher.h"
#include "PowerNode.h"

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
		glm::vec2 prosPos = pCamera->transformPosition(pObjectCollection->getClosestControllablePosition(currentID) - glm::vec2(10,10));
		glm::vec2 curPos = pCamera->transformPosition(pConsole->getControlPosition() - glm::vec2(10, 10));
		pSpriteCollection->setAbsoluteMode(true);
		pSpriteCollection->addImageDraw(pSpriteCollection->getPointerFromName("switcher_overlay_current"), curPos.x, curPos.y, 1000000, pSpriteCollection->getScale(), 10, 10);
		pSpriteCollection->addImageDraw(pSpriteCollection->getPointerFromName("switcher_overlay_prospect"), prosPos.x, prosPos.y, 1000000, pSpriteCollection->getScale(), 10, 10);
		pSpriteCollection->setAbsoluteMode(false);
	}

	std::shared_ptr<PowerNode> tempNode = std::dynamic_pointer_cast<PowerNode>(pObjectCollection->getObjectById(currentID));
	
	if (tempNode != nullptr) {
		float e = tempNode->getPercentage();
		pSpriteCollection->setAbsoluteMode(true);
		int a = 4;
		int b = 4;
		int c = 140;
		int d = 30;
		int x = 50;
		int y = 50;
		pSpriteCollection->addRectDraw(x, y, c, a, -10, sf::Color(50, 50, 50, 255));
		pSpriteCollection->addRectDraw(x, y, a, d, -10, sf::Color(50, 50, 50, 255));
		pSpriteCollection->addRectDraw(x, y + d - a, c, a, -10, sf::Color(50, 50, 50, 255));
		pSpriteCollection->addRectDraw(x + c - a, y, a, d, -10, sf::Color(50, 50, 50, 255));
		pSpriteCollection->addRectDraw(x + a + b, y + a + b, e * float(c - 2 * (a + b)), (d - 2 * (a + b)), -10, sf::Color(139, 224, 255, 180));
		//pSpriteCollection->addTextDraw(2, 150, 50, -100, std::to_string(std::dynamic_pointer_cast<PowerNode>(pObjectCollection->getObjectById(currentID))->getPercentage()), 20, sf::Color(255, 255, 255, 255));
		//pSpriteCollection->addRectDraw(50, 50, 1000, 50, -10, sf::Color(255, 255, 255, 255));
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

int ControlSwitcher::getControllingId() {
	return currentID;
}

Inventory* ControlSwitcher::getControllingInventory() {
	return pObjectCollection->getObjectById(currentID)->getInventory();
}

