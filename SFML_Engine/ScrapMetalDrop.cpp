#include "ScrapMetalDrop.h"

ScrapMetalDrop::ScrapMetalDrop(SpriteCollection* _pSpriteCollection, int _x, int _y, b2World* _pPhysicsWorld) :
	Object(_x, _y, 24, 24, 0, movable, true, _pPhysicsWorld) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	pSpriteCollection = _pSpriteCollection;
	spriteStack = SpriteStack(pSpriteCollection, "scrap_drop_stack_1", 12, 12, 10, 2);
	canBePickedUp = true;
	type = objectCrate;
	sellable = true;

	// Create a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(_x, _y);
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

void ScrapMetalDrop::draw() {
	rotation += 2;
	spriteStack.draw(boundingBox.x, boundingBox.y, boundingBox.y, rotation);
}

void ScrapMetalDrop::update(){
	b2Vec2 position = physicsBody->GetPosition();
	boundingBox.x = position.x;
	boundingBox.y = position.y;
	/*float speed = sqrt(boundingBox.xv * boundingBox.xv + boundingBox.yv * boundingBox.yv);
	if (speed > 5) {
		boundingBox.xv *= 10 / speed;
		boundingBox.yv *= 10 / speed;
	}
	boundingBox.xv *= 0.7;
	boundingBox.yv *= 0.7;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;*/

}
