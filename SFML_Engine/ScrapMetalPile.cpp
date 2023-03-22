#include "ScrapMetalPile.h"

ScrapMetalPile::ScrapMetalPile(SpriteCollection* _pSpriteCollection, int _x, int _y, b2World* _pPhysicsWorld) :
	Object(_x, _y, 32, 32, 0, immovable, true, _pPhysicsWorld
	),
	Mineable(10) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	spriteStack = SpriteStack(pSpriteCollection, "scrap_stack_1", 16, 16, 16, 2);
	canBePickedUp = false;
	type = objectCrate;

	// Create a kinematic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(_x, _y);
	physicsBody = pPhysicsWorld->CreateBody(&bodyDef);

	// Attach a shape to the kinematic body
	b2PolygonShape kinematicBox;
	kinematicBox.SetAsBox(boundingBox.w / 2, boundingBox.h / 2);
	physicsBody->CreateFixture(&kinematicBox, 0.0f);

	physicsBodyType = 1;
}

void ScrapMetalPile::draw() {
	spriteStack.draw(boundingBox.x, boundingBox.y, boundingBox.y, rotation);
}