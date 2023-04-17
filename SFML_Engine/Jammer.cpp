#include "Jammer.h"

Jammer::Jammer(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, int _x, int _y, b2World* _pPhysicsWorld) :
	Object(_x, _y, 16, 16, 0, immovable, true, _pPhysicsWorld),
		Living(100, 2, factionFriendly) {
		boundingBox.x = _x;
		boundingBox.y = _y;
		pSpriteCollection = _pSpriteCollection;
		pConsole = _pConsole;
		pSoundPlayer = _pSoundPlayer;
		spriteStack = SpriteStack(pSpriteCollection, "jammer_stack_1", 8, 8, 16, 2);
		canBePickedUp = true;
		type = objectMarketRelay;
		AmbientSoundId = pSoundPlayer->playSoundByName("jammer_ambient_1", 0.1);
		pSoundPlayer->loopSound(AmbientSoundId);

		// Create a kinematic body
		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set((float)_x / 100, (float)_y / 100);
		physicsBody = pPhysicsWorld->CreateBody(&bodyDef);

		// Attach a shape to the kinematic body
		b2PolygonShape kinematicBox;
		kinematicBox.SetAsBox((boundingBox.w / 2) / 100, (boundingBox.h / 2) / 100);
		physicsBody->CreateFixture(&kinematicBox, 0.0f);

		physicsBodyType = 1;
}

Jammer::~Jammer() {
	pSoundPlayer->stopSound(AmbientSoundId);
}

void Jammer::draw(){
	spriteStack.draw(boundingBox.x, boundingBox.y, boundingBox.y, rotation);
	//spriteSheet.draw(boundingBox.x, boundingBox.y-30, boundingBox.y);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + 8, boundingBox.y + 8 - 32), glm::vec3(160, 214, 255), 2, 1, false);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + 8, boundingBox.y + 8 - 32), glm::vec3(160, 214, 255), 0.2, 0, false);
}

void Jammer::update(){
	pSoundPlayer->setVolume(AmbientSoundId, 0.05 * pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
	physicsBody->SetTransform(b2Vec2(boundingBox.x / 100, boundingBox.y / 100), rotation);
}

void Jammer::onDeath(){
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x, getCenter().y);
}
