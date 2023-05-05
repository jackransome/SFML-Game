#include "ScrapMetalDrop.h"

ScrapMetalDrop::ScrapMetalDrop(SpriteCollection* _pSpriteCollection, int _x, int _y, b2World* _pPhysicsWorld) :
	Object(_x, _y, 24, 24, 0, movable, true, _pPhysicsWorld) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	spriteStack = SpriteStack(pSpriteCollection, "scrap_drop_stack_1", 12, 12, 10, 2);
	spriteStack.setRasterizeMode(false);
	canBePickedUp = true;
	type = objectScrapMetalDrop;
	sellable = true;

	// Create a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((float)_x/100, (float)_y/100);
	physicsBody = pPhysicsWorld->CreateBody(&bodyDef);

	// Attach a shape to the dynamic body
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((boundingBox.w / 2)/100, (boundingBox.h / 2) / 100);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.01f;
	fixtureDef.friction = 20.01f;
	physicsBody->CreateFixture(&fixtureDef);

	physicsBodyType = 2;
}

void ScrapMetalDrop::draw() {
	rotation += 2;
	spriteStack.draw(boundingBox.x, boundingBox.y, boundingBox.y, rotation);
}

void ScrapMetalDrop::update(){
	if (!pickedUp) {
		b2Vec2 position = physicsBody->GetPosition();
		boundingBox.x = position.x*100;
		boundingBox.y = position.y*100;
		physicsBody->SetTransform(position, rotation);
	}

	if (pickedUp) {
		physicsBody->SetTransform(b2Vec2(boundingBox.x/100, boundingBox.y/100), rotation);
	}
}
