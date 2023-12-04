#include "Builder.h"

// Define the map
std::map<BuildType, CostData> costMap = {
	{ BuildType::autoTurret, {2, 0, 0, objectAutoTurret} },
	{ BuildType::teleporterPillar, {6, 0, 0, objectTeleporterPillar} },
	{ BuildType::relay, {2, 4, 0, objectRelay} },
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
		if (pInputManager->onKeyDown(mouseR) || pInputManager->onKeyDown(mouseM)) {
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
		pSpriteCollection->setAbsoluteMode(true);
		pSpriteCollection->addImageDraw(pSpriteCollection->getPointerFromName("builder_crosshair"), pInputManager->mouseX-11, pInputManager->mouseY-11, 1000000, 2, 22, 22);
		pSpriteCollection->setAbsoluteMode(false);
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
