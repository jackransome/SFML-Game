#include "Builder.h"

// Define the map
std::map<BuildType, CostData> costMap = {
	{ BuildType::autoTurret, {2, 0, 0, objectAutoTurret} },
	{ BuildType::teleporter, {6, 0, 0, objectAutoTurret} },
	{ BuildType::relay, {4, 0, 0, objectRelay} },
	{ BuildType::generator, {8, 0, 0, objectGenerator} }
};

Builder::Builder(SpriteCollection* _pSpriteCollection, Inventory* _pInventory, Console* _pConsole, InputManager* _pInputManager){
	pSpriteCollection = _pSpriteCollection;
	pInventory = _pInventory;
	pConsole = _pConsole;
	pInputManager = _pInputManager;
}

bool Builder::getActive() {
	return active;
}

void Builder::activate(BuildType buildType){
	currentBuildType = buildType;
	active = true;
}

void Builder::cancel(){
	active = false;
}

void Builder::update(){
	if (active) {
		if (pInputManager->onKeyDown(mouseR)) {
			active = false;
			return;
		}
		if (pInputManager->onKeyDown(mouseL)) {
			mouseLDown = true;
		}
		if (mouseLDown && pInputManager->onKeyUp(mouseL)) {
			if (checkResources(currentBuildType)) {
				buy(currentBuildType);
				pConsole->addCommand(commandAddBuildObject, costMap[currentBuildType].objectType, pInputManager->translatedMouseX, pInputManager->translatedMouseY);
			}
			active = false;
			mouseLDown = false;
		}
		pInputManager->disableMouseButtons();
	}
	else {
		mouseLDown = false;
	}
}

void Builder::draw(){
	if (active) {

	}
}

bool Builder::checkResources(BuildType buildType){
	if (pInventory->getResources(Resource::scrap) < costMap[buildType].scrap) {
		return false;
	}
	if (pInventory->getResources(Resource::component) < costMap[buildType].components) {
		return false;
	}
	return true;
}



void Builder::buy(BuildType buildType){
	pInventory->removeResources(Resource::scrap, costMap[buildType].scrap);
	pInventory->removeResources(Resource::component, costMap[buildType].components);
}
