#include "Builder.h"

// Define the map
std::map<BuildType, CostData> costMap = {
	{ BuildType::autoTurret, {2, 0, 0, objectAutoTurret} },
	{ BuildType::rover, {4, 0, 0, objectRover} },
	{ BuildType::relay, {4, 0, 0, objectRelay} },
	{ BuildType::generator, {8, 0, 0, objectGenerator} },
	{ BuildType::teleporterPillar, {0, 4, 0, objectTeleporterPillar} },
	{ BuildType::buildDrone, {9, 0, 0, objectBuildDrone} }
};

std::map<BuildType, int> sizeMap = {
	{ BuildType::autoTurret, 24 },
	{ BuildType::rover, 24 },
	{ BuildType::relay, 20 },
	{ BuildType::generator, 34 },
	{ BuildType::buildDrone, 5 }
};

Builder::Builder(SpriteCollection* _pSpriteCollection, Inventory* _pInventory, Console* _pConsole, InputManager* _pInputManager, ObjectCollection* _pObjectCollection){
	pSpriteCollection = _pSpriteCollection;
	pInventory = _pInventory;
	pConsole = _pConsole;
	pInputManager = _pInputManager;
	pObjectCollection = _pObjectCollection;
}

bool Builder::getActive() {
	return active;
}

void Builder::activate(BuildType buildType){
	currentBuildType = buildType;
	active = true;
	rotation = ((float)rand() / (float)RAND_MAX)*360;
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
		if (pInputManager->isKeyDown(q)) {
			rotation -= 5;
		}
		if (pInputManager->isKeyDown(e)) {
			rotation += 5;
		}
		if (pInputManager->onKeyDown(mouseL)) {
			mouseLDown = true;
		}
		if (mouseLDown && pInputManager->onKeyUp(mouseL)) {
			if (pObjectCollection->checkArea(glm::vec4(pInputManager->translatedMouseX - (sizeMap[currentBuildType]/2), pInputManager->translatedMouseY - (sizeMap[currentBuildType] / 2), sizeMap[currentBuildType], sizeMap[currentBuildType]))) {
				if (checkResources(currentBuildType)) {
					buy(currentBuildType);
					pConsole->addCommand(commandAddBuildObject, costMap[currentBuildType].objectType, pInputManager->translatedMouseX, pInputManager->translatedMouseY);
					pConsole->addCommand(commandSetLastRotation, rotation);
				}
				active = false;
				mouseLDown = false;
			}
		}
		pInputManager->disableMouseButtons();
	}
	else {
		mouseLDown = false;
	}
}

void Builder::draw(){
	if (active) {
		if (pObjectCollection->checkArea(glm::vec4(pInputManager->translatedMouseX - (sizeMap[currentBuildType] / 2), pInputManager->translatedMouseY - (sizeMap[currentBuildType] / 2), sizeMap[currentBuildType], sizeMap[currentBuildType]))) {
			pSpriteCollection->setAbsoluteMode(true);
			pSpriteCollection->addRotatedImageDraw(pSpriteCollection->getPointerFromName("builder_crosshair"), pInputManager->mouseX - 11, pInputManager->mouseY - 11, 1000000, 2 * pSpriteCollection->getScale(), rotation, 22 * pSpriteCollection->getScale(), 22 * pSpriteCollection->getScale());
			//pSpriteCollection->addRotatedImageDrawCut(pSpriteCollection->getPointerFromName("builder_crosshair"), pInputManager->mouseX - 11, pInputManager->mouseY - 11, 0, 0, 0, 11, 11, 2, rotation);
			pSpriteCollection->setAbsoluteMode(false);
		}
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

int Builder::getScrapNeeded(BuildType buildType)
{
	return costMap[buildType].scrap;
}

int Builder::getComponentsNeeded(BuildType buildType)
{
	return costMap[buildType].components;
}



void Builder::buy(BuildType buildType){
	pInventory->removeResources(Resource::scrap, costMap[buildType].scrap);
	pInventory->removeResources(Resource::component, costMap[buildType].components);
}
