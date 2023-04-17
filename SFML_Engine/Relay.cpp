#include "Relay.h"

Relay::Relay(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, int _x, int _y, b2World* _pPhysicsWorld) :
	Object(x, y, 20, 20, 0, immovable, true, _pPhysicsWorld),
	Living(100, 2, factionFriendly),
	Controllable(500) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	pConsole = _pConsole;
	pSoundPlayer = _pSoundPlayer;
	spriteStack = SpriteStack(pSpriteCollection, "relay_stack_1", 13, 13, 34, 2);
	AmbientSoundId = pSoundPlayer->playSoundByName("relay_ambient_3", 0.1);
	pSoundPlayer->loopSound(AmbientSoundId);
	canBePickedUp = true;
	type = objectRelay;

	// Create a kinematic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set((float)_x/100, (float)_y/100);
	physicsBody = pPhysicsWorld->CreateBody(&bodyDef);

	// Attach a shape to the kinematic body
	b2PolygonShape kinematicBox;
	kinematicBox.SetAsBox((boundingBox.w / 2)/100, (boundingBox.h / 2) / 100);
	physicsBody->CreateFixture(&kinematicBox, 0.0f);

	physicsBodyType = 1;
}

Relay::~Relay(){
	pSoundPlayer->stopSound(AmbientSoundId);
}

void Relay::draw() {
	float lightPhase = 0.7f+sin(pConsole->getFrame()/80.0f)/2.0f;
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 68), glm::vec3(160, 214, 255), 2* lightPhase, 1, false);
	pSpriteCollection->drawLightSource(glm::vec2(boundingBox.x + boundingBox.w / 2, boundingBox.y + boundingBox.h / 2 - 68), glm::vec3(160, 214, 255), 0.2* lightPhase, 0, false);
	spriteStack.draw(boundingBox.x-3, boundingBox.y-3, boundingBox.y-3, rotation);
}

void Relay::onDeath(){
	pConsole->addCommand(commandAddObject, objectScrapMetalDrop, getCenter().x, getCenter().y);
}

void Relay::update(){
	pSoundPlayer->setVolume(AmbientSoundId, 0.5*pSoundPlayer->getSpatialVolume(pConsole->getControlPosition(), getCenter()));
	physicsBody->SetTransform(b2Vec2(boundingBox.x/100, boundingBox.y/100), rotation);
}
