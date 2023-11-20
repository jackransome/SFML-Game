#include "MarketRelay.h"

MarketRelay::MarketRelay(SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Console* _pConsole, SoundPlayer* _pSoundPlayer, int _x, int _y, b2World* _pPhysicsWorld) :
	Object(_x, _y, 22, 22, 0, immovable, true, _pPhysicsWorld),
	Living(100, 2, factionFriendly),
	Controllable(200) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	pInputManager = _pInputManager;
	pConsole = _pConsole;
	pSoundPlayer = _pSoundPlayer;
	//spriteSheet = SpriteSheet(pSpriteCollection, "market_relay", 11, 26, 1, 2);
	spriteStack = SpriteStack(pSpriteCollection, "market_relay_stack_1", 12, 12, 30, 2);
	canBePickedUp = true;
	type = objectMarketRelay;
	AmbientSoundId = pSoundPlayer->playSoundByName("relay_ambient_2", 0.1);
	pSoundPlayer->loopSound(AmbientSoundId);
	sellSpaceWidth = 200;
	sellSpaceHeight = 200;

	// Create a kinematic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set((float)_x/100, (float)_y/100);
	physicsBody = pPhysicsWorld->CreateBody(&bodyDef);

	// Attach a shape to the kinematic body
	b2PolygonShape kinematicBox;
	kinematicBox.SetAsBox((boundingBox.w/2) / 100, (boundingBox.h/2)/100);
	physicsBody->CreateFixture(&kinematicBox, 0.0f);

	physicsBodyType = 1;
}

MarketRelay::~MarketRelay(){
	pSoundPlayer->stopSound(AmbientSoundId);
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
		if (pInputManager->onKeyDown(u)) {
			if (credits >= 5) {
				pConsole->addCommand(commandAddObject, objectJammer, pInputManager->translatedMouseX, pInputManager->translatedMouseY);
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
	pSoundPlayer->setVolume(AmbientSoundId, 0.3*pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
	physicsBody->SetTransform(b2Vec2(boundingBox.x/100, boundingBox.y/100), rotation);
}

void MarketRelay::onDeath(){
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x, getCenter().y);
}

void MarketRelay::addCredit(int _credit){
	credits += _credit;
}

void MarketRelay::draw() {
	if (controlled) {
		pSpriteCollection->setFullBrightMode(true);
		pSpriteCollection->addAbsoluteTextDraw(1, 50, 50, 1000000, std::to_string(credits), 40, sf::Color(255, 255, 255, 255));
		pSpriteCollection->setFullBrightMode(false);
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
		pSpriteCollection->setFullBrightMode(true);
		pSpriteCollection->addRectDraw(finalStartPoint.x, finalStartPoint.y, finalEndPoint.x - finalStartPoint.x, finalEndPoint.y - finalStartPoint.y, 300, sf::Color(255, 255, 255, 100));
		pSpriteCollection->setFullBrightMode(false);
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
	spriteStack.draw(boundingBox.x - 1, boundingBox.y - 1, boundingBox.y - 1, rotation);
	//spriteSheet.draw(boundingBox.x, boundingBox.y-30, boundingBox.y);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + 11, boundingBox.y + 11 - 60), glm::vec3(160, 214, 255), 2, 1);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + 11, boundingBox.y + 11 - 60), glm::vec3(160, 214, 255), 0.2, 0);
}