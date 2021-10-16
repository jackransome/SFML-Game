#include "CommandExecuter.h"

CommandExecuter::CommandExecuter() {}

CommandExecuter::CommandExecuter(ObjectCollection* _pObjectCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera){
	pObjectCollection = _pObjectCollection;
	pSoundPlayer = _pSoundPlayer;
	pCamera = _pCamera;
}

void CommandExecuter::execute(Command command) {
	switch (command.type) {
	case commandAddObject:
		switch (command.objectType) {
		case objectFootprint:
			pObjectCollection->addFootPrint(command.f1, command.f2);
				break;
		default:
			std::cout << "UNKNOWN OBJECT";
		}
		break;
	case commandPlaySound:
		pSoundPlayer->playSoundByName(command.string);
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
	default:
		std::cout << "UNKNOWN COMMAND";
	}
}
