#include "ObjectCollection.h"
#include "CollisionDetection.h"

ObjectCollection::ObjectCollection() {}

ObjectCollection::ObjectCollection(Console* _pConsole, InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera) {
	pConsole = _pConsole;
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	pSoundPlayer = _pSoundPlayer;
	pCamera = _pCamera;
}

void ObjectCollection::draw() {
	if (!debug) {
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->draw();
		}
	}
	else {
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->draw();
			pSpriteCollection->addRectDraw(objects[i]->getBoundingBox().x, objects[i]->getBoundingBox().y, objects[i]->getBoundingBox().w, objects[i]->getBoundingBox().h, 10000, sf::Color(0, 255, 0, 100));
		}
	}
}

void ObjectCollection::update() {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getToDestroy()) {
			objects.erase(objects.begin() + i);
			i--;
			continue;
		}
		objects[i]->update();
	}
}

void ObjectCollection::addMainCharacter(float x, float y) {
	objects.push_back(new MainCharacter(pInputManager, pSpriteCollection, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addFootPrint(float x, float y) {
	objects.push_back(new FootPrint(pSpriteCollection, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addWall(int x, int y, int w, int h) {
	objects.push_back(new Wall(pSpriteCollection, x, y, w, h));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::setLatestId() {
	objects[objects.size() - 1]->setId(nextId);
	nextId++; //when is this gonna overflow
}

void ObjectCollection::setLatestConsole() {
	objects[objects.size() - 1]->setConsolePointer(pConsole);
}

void ObjectCollection::runCollisionDetection() {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getCollidability() == immovable) {
			for (int j = 0; j < objects.size(); j++) {
				if (objects[j]->getCollidability() == movable) {
					CollisionDetection::correctPosition(objects[j]->getBoundingBoxPointer(), objects[i]->getBoundingBoxPointer());
				}
			}
		}
	}
}

void ObjectCollection::setDebug(bool _debug) {
	debug = _debug;
}
