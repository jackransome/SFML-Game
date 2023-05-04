#include "Wall.h"

Wall::Wall(SpriteCollection* _pSpriteCollection, int _x, int _y, int width, int height, b2World* _pPhysicsWorld) :
	Object(_x, _y, width, height, 0, immovable, false, _pPhysicsWorld) {
	pSpriteCollection = _pSpriteCollection;
	type = objectWall;
	sideImage = pSpriteCollection->getPointerFromName("wall_texture1");
	topImage = pSpriteCollection->getPointerFromName("platform_top_main");
	edgeImage = pSpriteCollection->getPointerFromName("platform_top_edge");

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

void Wall::draw() {
	//pSpriteCollection->addRectDraw(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, boundingBox.y, sf::Color(40, 40, 40, 255));
	pSpriteCollection->addImageDrawCut(sideImage, boundingBox.x, boundingBox.y + boundingBox.h - 50, boundingBox.y + boundingBox.h, 0, 0, boundingBox.w, 50, 1);
	//pSpriteCollection->addShaderToLast("test");
	pSpriteCollection->addImageDrawCut(edgeImage, boundingBox.x, boundingBox.y - 50, boundingBox.y + boundingBox.h, 2000 - boundingBox.w, 2000 - boundingBox.h, boundingBox.w, boundingBox.h, 1);
	//pSpriteCollection->addShaderToLast("test");
	pSpriteCollection->addImageDrawCut(topImage, boundingBox.x, boundingBox.y - 50, boundingBox.y + boundingBox.h, 0, 0, boundingBox.w, boundingBox.h, 1);
	//pSpriteCollection->addShaderToLast("test");
}