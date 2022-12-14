#include "MarketRelay.h"

MarketRelay::MarketRelay(SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Console* _pConsole, SoundPlayer* _pSoundPlayer, int _x, int _y) :
	Object(_x, _y, 22, 22, 0, immovable, true),
	Living(100, 2),
	Controllable(200) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	pInputManager = _pInputManager;
	pConsole = _pConsole;
	pSoundPlayer = _pSoundPlayer;
	spriteSheet = SpriteSheet(pSpriteCollection, "market_relay", 11, 26, 1, 2);
	canBePickedUp = true;
	type = objectCrate;
	AmbientSoundId = pSoundPlayer->playSoundByName("relay_ambient_2", 0.1);
	pSoundPlayer->loopSound(AmbientSoundId);
}

void MarketRelay::update() {
	if (controlled) {
		//sell
		if (pInputManager->isKeyDown(e)) {
			// sell command with start point and w and h, and marketrelay id to add credits to
			if (pInputManager->onKeyDown(mouseL)) {
				startPoint = glm::vec2(pInputManager->translatedMouseX, pInputManager->translatedMouseY);
				startPointValid = true;
			}
			if (!pInputManager->isKeyDown(mouseL) && startPointValid) {
				if (startPointValid) {
					if (startPoint.x < pInputManager->translatedMouseX) {
						if (startPoint.y < pInputManager->translatedMouseY) {
							pConsole->addCommand(commandSellObjects, startPoint.x, startPoint.y, pInputManager->translatedMouseX - startPoint.x, pInputManager->translatedMouseY - startPoint.y, id);
						}
						else {
							pConsole->addCommand(commandSellObjects, startPoint.x, pInputManager->translatedMouseY, pInputManager->translatedMouseX - startPoint.x, startPoint.y - pInputManager->translatedMouseY, id);
						}
					}
					else {
						if (startPoint.y < pInputManager->translatedMouseY) {
							pConsole->addCommand(commandSellObjects, pInputManager->translatedMouseX, startPoint.y, startPoint.x - pInputManager->translatedMouseX, pInputManager->translatedMouseY - startPoint.y, id);
						}
						else {
							pConsole->addCommand(commandSellObjects, pInputManager->translatedMouseX, pInputManager->translatedMouseY, startPoint.x - pInputManager->translatedMouseX, startPoint.y - pInputManager->translatedMouseY, id);
						}
					}
					startPointValid = false;
				}
			}
		}
		else {
			startPointValid = false;
		}
	}
	pSoundPlayer->setVolume(AmbientSoundId, pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
}

void MarketRelay::onDeath(){
	pSoundPlayer->stopSound(AmbientSoundId);
}

void MarketRelay::addCredit(int _credit){
	credits += _credit;
}

void MarketRelay::draw() {
	if (controlled) {
		pSpriteCollection->addAbsoluteTextDraw(1, 50, 50, 1000000, std::to_string(credits), 20, sf::Color(255, 255, 255, 255));
		//draw menu
	}
	if (startPointValid) {
		if (startPoint.x < pInputManager->translatedMouseX) {
			if (startPoint.y < pInputManager->translatedMouseY) {
				pSpriteCollection->addRectDraw(startPoint.x, startPoint.y, pInputManager->translatedMouseX - startPoint.x, pInputManager->translatedMouseY - startPoint.y, 1000000, sf::Color(255, 255, 255, 50));
			}
			else {
				pSpriteCollection->addRectDraw(startPoint.x, pInputManager->translatedMouseY, pInputManager->translatedMouseX - startPoint.x, startPoint.y - pInputManager->translatedMouseY, 1000000, sf::Color(255, 255, 255, 50));
			}
		}
		else {
			if (startPoint.y < pInputManager->translatedMouseY) {
				pSpriteCollection->addRectDraw(pInputManager->translatedMouseX, startPoint.y, startPoint.x - pInputManager->translatedMouseX, pInputManager->translatedMouseY - startPoint.y, 1000000, sf::Color(255, 255, 255, 50));
			}
			else {
				pSpriteCollection->addRectDraw(pInputManager->translatedMouseX, pInputManager->translatedMouseY, startPoint.x - pInputManager->translatedMouseX, startPoint.y - pInputManager->translatedMouseY, 1000000, sf::Color(255, 255, 255, 50));
			}
		}
	}
	spriteSheet.draw(boundingBox.x, boundingBox.y-30, boundingBox.y);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + 11, boundingBox.y - 30), glm::vec3(160, 214, 255), 2, 1, false);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + 11, boundingBox.y - 30), glm::vec3(160, 214, 255), 0.2, 0, false);
}