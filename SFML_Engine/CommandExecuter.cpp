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
		if (command.f1) {
			pObjectCollection->setDebug(true);
		}
		else {
			pObjectCollection->setDebug(false);
		}
		break;
	case commandSetCameraPos:
		pCamera->setPosition(command.f1, command.f2);
		break;
	case commandDrawGreenRect:
		pSpriteCollection->addRectDraw(0, 0, 50, 50, 0, sf::Color(0, 255, 0, 255));
		break;
	case commandDrawRedRect:
		pSpriteCollection->addRectDraw(0, 50, 50, 50, 0, sf::Color(255, 0, 0, 255));
		break;
	case commandDoAEODamage:
		pObjectCollection->doAEODamage(command.f1, command.f2, command.f3, command.f4);
		break;
	case commandDamageAtMouse:
		pObjectCollection->doAEODamage(pInputManager->translatedMouseX, pInputManager->translatedMouseY, 30, command.f1);
		break;
	default:
		std::cout << "UNKNOWN COMMAND";
	}
}
