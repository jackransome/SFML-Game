#include "CommandExecuter.h"

CommandExecuter::CommandExecuter() {}

CommandExecuter::CommandExecuter(ObjectCollection* _pObjectCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera, SpriteCollection* _pSpriteCollection, InputManager* _pInputManager){
	pObjectCollection = _pObjectCollection;
	pSoundPlayer = _pSoundPlayer;
	pCamera = _pCamera;
	pSpriteCollection = _pSpriteCollection;
	pInputManager = _pInputManager;
}

void CommandExecuter::execute(Command command) {
	switch (command.type) {
	case commandAddObject:
		switch (command.objectType) {
		case objectFootprint:
			pObjectCollection->addFootPrint(command.f1, command.f2);
				break;
		case objectAction1animation:
			pObjectCollection->addAction1Animation(command.f1, command.f2);
			break;
		case objectRoverTracks:
			pObjectCollection->addRoverTracks(command.f1, command.f2, command.f3);
			break;
		case objectScrapMetalDrop:
			pObjectCollection->addScapMetalDrop(command.f1, command.f2);
			break;
		default:
			std::cout << "UNKNOWN OBJECT";
		}
		break;
	case commandPlaySound:
		pSoundPlayer->playSoundByName(command.string, command.f1, command.f2);
		break;
	case commandLoopSound:
		pSoundPlayer->loopSound(command.a);
		break;
	case commandStopSound:
		pSoundPlayer->stopSound(command.a);
		break;
	case commandShakeScreen:
		pCamera->addScreenshake(command.f1);
		break;
	case commandEnableDebug:
		if (command.a) {
			pObjectCollection->setDebug(true);
		}
		else {
			pObjectCollection->setDebug(false);
		}
		break;
	case commandSetCameraPos:
		pCamera->setPosition(command.f1, command.f2);
		break;
	case commandSetCameraFocusId:
		pObjectCollection->setCameraFocus(command.a);
		break;
	case commandDrawGreenRect:
		pSpriteCollection->addRectDraw(0, 0, 50, 50, 0, sf::Color(0, 255, 0, 255));
		break;
	case commandDrawRedRect:
		pSpriteCollection->addRectDraw(0, 50, 50, 50, 0, sf::Color(255, 0, 0, 255));
		break;
	case commandDoAEODamage:
		pObjectCollection->doAEODamage(command.f1, command.f2, command.f3, command.f4, command.a);
		break;
	case commandDamageAtMouse:
		pObjectCollection->doAEODamage(pInputManager->translatedMouseX, pInputManager->translatedMouseY, 30, command.f1, -1);
		break;
	case commandEnableObjectControls:
		pObjectCollection->resetAllControls();
		pObjectCollection->setControls(command.a, true);
		break;
	case commandDisableObjectControls:
		pObjectCollection->setControls(command.a, false);
		break;
	case commandPickUp:
		pObjectCollection->runPickUp(command.a);
		break;
	case commandDrop:
		pObjectCollection->runDrop(command.a);
		break;
	case commandSellObjects:
		pObjectCollection->sellObjects(command.f1, command.f2, command.f3, command.f4, command.a);
		break;
	case commandBlink:
		pSpriteCollection->blink();
		break;
	case commandAddProjectile:
		pObjectCollection->addProjectile(command.f1, command.f2, command.f3, command.f4, command.a);
		break;
	default:
		std::cout << "UNKNOWN COMMAND";
	}
}
