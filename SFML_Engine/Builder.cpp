#include "Builder.h"

Builder::Builder(SpriteCollection* _pSpriteCollection, Inventory* _pInventory, Console* _pConsole, InputManager* _pInputManager){
	pSpriteCollection = _pSpriteCollection;
	pInventory = _pInventory;
	pConsole = _pConsole;
	pInputManager = _pInputManager;
}

bool Builder::hasResources(BuildType buildType)
{
	switch (buildType) {
	case BuildType::turret:
		if (pInventory->getResources(Resource::scrap) >= 2) {
			return true;
		}
		break;
	}
	return false;
}

void Builder::activate(BuildType buildType){
	currentBuildType = buildType;
	active = true;
}

void Builder::cancel(){
	active = false;
}

void Builder::update(){
	if (pInputManager->onKeyDown(mouseL)) {
		buy(currentBuildType);
		switch (currentBuildType) {
		case BuildType::turret:
			if (pInventory->getResources(Resource::scrap) >= 2) {
				pConsole->addCommand(commandAddObject, objectAutoTurret, pInputManager->translatedMouseX, pInputManager->translatedMouseY);
			}
			break;
		}
	}
}

void Builder::draw(){
	if (active) {

	}
}

void Builder::buy(BuildType buildType){
	switch (buildType) {
	case BuildType::turret:
		pInventory->removeResources(Resource::scrap, 2);
		break;
	}
}
