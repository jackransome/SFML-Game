#include "MarketRelay.h"

MarketRelay::MarketRelay(SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Console* _pConsole, SoundPlayer* _pSoundPlayer, int _x, int _y) :
	Object(_x, _y, 22, 22, 0, immovable, true),
	Living(100, 2, factionFriendly),
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
	selectionBox = pSpriteCollection->getPointerFromName("white_rect");
	pSoundPlayer->loopSound(AmbientSoundId);
	sellSpaceWidth = 200;
	sellSpaceHeight = 200;
}

void MarketRelay::update() {
	if (controlled) {
		//buy
		if (pInputManager->onKeyDown(y)) {
			if (credits >= 5) {
				pConsole->addCommand(commandAddObject, objectAutoTurret, pInputManager->translatedMouseX, pInputManager->translatedMouseY);
				credits -= 5;
			}
		}

		//sell
		if (pInputManager->isKeyDown(e)) {
			glm::vec2 center = getCenter();
			// sell command with start point and w and h, and marketrelay id to add credits to
			if (pInputManager->onKeyDown(mouseL) && pInputManager->translatedMouseX > center.x - sellSpaceWidth/2 && pInputManager->translatedMouseX < center.x + sellSpaceWidth / 2 && pInputManager->translatedMouseY > center.y - sellSpaceHeight / 2 && pInputManager->translatedMouseY < center.y + sellSpaceHeight / 2) {
				startPoint = glm::vec2(pInputManager->translatedMouseX, pInputManager->translatedMouseY);
				startPointValid = true;
			}
			if (!pInputManager->isKeyDown(mouseL) && startPointValid) {
				if (startPointValid) {
					
					glm::vec2 finalStartPoint;
					glm::vec2 finalEndPoint;
					if (startPoint.x < pInputManager->translatedMouseX) {
						if (startPoint.y < pInputManager->translatedMouseY) {
							finalStartPoint = glm::vec2(startPoint.x, startPoint.y);
							finalEndPoint = glm::vec2(pInputManager->translatedMouseX, pInputManager->translatedMouseY);
							//pConsole->addCommand(commandSellObjects, std::min(startPoint.x, center.x - ), startPoint.y, pInputManager->translatedMouseX - startPoint.x, pInputManager->translatedMouseY - startPoint.y, id);
						}
						else {
							finalStartPoint = glm::vec2(startPoint.x, pInputManager->translatedMouseY);
							finalEndPoint = glm::vec2(pInputManager->translatedMouseX, startPoint.y);
							//pConsole->addCommand(commandSellObjects, startPoint.x, pInputManager->translatedMouseY, pInputManager->translatedMouseX - startPoint.x, startPoint.y - pInputManager->translatedMouseY, id);
						}
					}
					else {
						if (startPoint.y < pInputManager->translatedMouseY) {
							finalStartPoint = glm::vec2(pInputManager->translatedMouseX, startPoint.y);
							finalEndPoint = glm::vec2(startPoint.x, pInputManager->translatedMouseY);
							//pConsole->addCommand(commandSellObjects, pInputManager->translatedMouseX, startPoint.y, startPoint.x - pInputManager->translatedMouseX, pInputManager->translatedMouseY - startPoint.y, id);
						}
						else {
							finalStartPoint = glm::vec2(pInputManager->translatedMouseX, pInputManager->translatedMouseY);
							finalEndPoint = glm::vec2(startPoint.x, startPoint.y);
							//pConsole->addCommand(commandSellObjects, pInputManager->translatedMouseX, pInputManager->translatedMouseY, startPoint.x - pInputManager->translatedMouseX, startPoint.y - pInputManager->translatedMouseY, id);
						}
					}
					finalStartPoint.x = std::max(finalStartPoint.x, center.x - sellSpaceWidth / 2);
					finalStartPoint.y = std::max(finalStartPoint.y, center.y - sellSpaceHeight / 2);
					finalEndPoint.x = std::min(finalEndPoint.x, center.x + sellSpaceWidth / 2);
					finalEndPoint.y = std::min(finalEndPoint.y, center.y + sellSpaceHeight / 2);
					pConsole->addCommand(commandSellObjects, finalStartPoint.x, finalStartPoint.y, finalEndPoint.x - finalStartPoint.x, finalEndPoint.y - finalStartPoint.y, id);

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
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x, getCenter().y);
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
		glm::vec2 center = getCenter();
		glm::vec2 finalStartPoint;
		glm::vec2 finalEndPoint;
		if (startPoint.x < pInputManager->translatedMouseX) {
			if (startPoint.y < pInputManager->translatedMouseY) {
				finalStartPoint = glm::vec2(startPoint.x, startPoint.y);
				finalEndPoint = glm::vec2(pInputManager->translatedMouseX, pInputManager->translatedMouseY);
				//pConsole->addCommand(commandSellObjects, std::min(startPoint.x, center.x - ), startPoint.y, pInputManager->translatedMouseX - startPoint.x, pInputManager->translatedMouseY - startPoint.y, id);
			}
			else {
				finalStartPoint = glm::vec2(startPoint.x, pInputManager->translatedMouseY);
				finalEndPoint = glm::vec2(pInputManager->translatedMouseX, startPoint.y);
				//pConsole->addCommand(commandSellObjects, startPoint.x, pInputManager->translatedMouseY, pInputManager->translatedMouseX - startPoint.x, startPoint.y - pInputManager->translatedMouseY, id);
			}
		}
		else {
			if (startPoint.y < pInputManager->translatedMouseY) {
				finalStartPoint = glm::vec2(pInputManager->translatedMouseX, startPoint.y);
				finalEndPoint = glm::vec2(startPoint.x, pInputManager->translatedMouseY);
				//pConsole->addCommand(commandSellObjects, pInputManager->translatedMouseX, startPoint.y, startPoint.x - pInputManager->translatedMouseX, pInputManager->translatedMouseY - startPoint.y, id);
			}
			else {
				finalStartPoint = glm::vec2(pInputManager->translatedMouseX, pInputManager->translatedMouseY);
				finalEndPoint = glm::vec2(startPoint.x, startPoint.y);
				//pConsole->addCommand(commandSellObjects, pInputManager->translatedMouseX, pInputManager->translatedMouseY, startPoint.x - pInputManager->translatedMouseX, startPoint.y - pInputManager->translatedMouseY, id);
			}
		}
		finalStartPoint.x = std::max(finalStartPoint.x, center.x - sellSpaceWidth / 2);
		finalStartPoint.y = std::max(finalStartPoint.y, center.y - sellSpaceHeight / 2);
		finalEndPoint.x = std::min(finalEndPoint.x, center.x + sellSpaceWidth / 2);
		finalEndPoint.y = std::min(finalEndPoint.y, center.y + sellSpaceHeight / 2);
		//(Image * pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float opacity)
		//pSpriteCollection->setFullBrightMode(true);
		pSpriteCollection->addImageDraw(selectionBox, finalStartPoint.x, finalStartPoint.y, 1000000, 0, 0, finalEndPoint.x - finalStartPoint.x, finalEndPoint.y - finalStartPoint.y, 1, 1);
		pSpriteCollection->addShaderToLast("test2");
		//pSpriteCollection->setFullBrightMode(false);
		//pSpriteCollection->addRectDraw(finalStartPoint.x, finalStartPoint.y, finalEndPoint.x - finalStartPoint.x, finalEndPoint.y - finalStartPoint.y, 1000000, sf::Color(255, 255, 255, 50));
		/*pSpriteCollection->addRectDraw(pInputManager->translatedMouseX, pInputManager->translatedMouseY, startPoint.x - pInputManager->translatedMouseX, startPoint.y - pInputManager->translatedMouseY, 1000000, sf::Color(255, 255, 255, 50));
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
		}*/
	}
	spriteSheet.draw(boundingBox.x, boundingBox.y-30, boundingBox.y);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + 11, boundingBox.y - 30), glm::vec3(160, 214, 255), 2, 1, false);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + 11, boundingBox.y - 30), glm::vec3(160, 214, 255), 0.2, 0, false);
}