#include "Crate.h"

Crate::Crate(SpriteCollection* _pSpriteCollection, int _x, int _y, b2World* _pPhysicsWorld) :
	Object(_x, _y, 20, 20, 0, immovable, true, _pPhysicsWorld) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	pPhysicsWorld = _pPhysicsWorld;
	spriteStack = SpriteStack(pSpriteCollection, "crate_stack_1", 10, 10, 6, 2);
	canBePickedUp = true;
	type = objectCrate;

	// Create a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(_x, _y);
	bodyDef.linearDamping = 1.0f;
	physicsBody = pPhysicsWorld->CreateBody(&bodyDef);

	// Attach a shape to the dynamic body
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(boundingBox.w / 2, boundingBox.h / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.01f;
	fixtureDef.friction = 0.01f;

	physicsBody->CreateFixture(&fixtureDef);

	physicsBodyType = 2;
	
}

void Crate::draw() {
	spriteStack.draw(boundingBox.x, boundingBox.y, boundingBox.y, rotation);
}

void Crate::update(){
	b2Vec2 position = physicsBody->GetPosition();
	rotation = physicsBody->GetAngle();
	boundingBox.x = position.x;
	boundingBox.y = position.y;
}
