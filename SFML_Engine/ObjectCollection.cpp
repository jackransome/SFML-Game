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

void ObjectCollection::addAction1Animation(float x, float y) {
	objects.push_back(new Action1Animation(pSpriteCollection, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addWall(int x, int y, int w, int h) {
	objects.push_back(new Wall(pSpriteCollection, x, y, w, h));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addEnemy(int x, int y) {
	objects.push_back(new Enemy(pSpriteCollection, x, y));
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

void ObjectCollection::drawHealthBars() {
	Living* living;
	for (int i = 0; i < objects.size(); i++) {
		//check if object inherits living
		if (living = dynamic_cast<Living*>(objects[i])) {
			pSpriteCollection->addRectDraw(objects[i]->getBoundingBox().x, objects[i]->getBoundingBox().y - 10, living->getHealth(), 5, -10000, sf::Color(0, 255, 0));
		}
	}
}

void ObjectCollection::doAEODamage(float x, float y, float range, float damage) {
	Living* living;
	for (int i = 0; i < objects.size(); i++) {
		//check if object inherits living
		if (living = dynamic_cast<Living*>(objects[i])) {
			//check if within range
			if (pow((objects[i]->getBoundingBox().x + objects[i]->getBoundingBox().w / 2) - x, 2) + pow((objects[i]->getBoundingBox().x + objects[i]->getBoundingBox().w / 2) - y, 2) < pow(range, 2)) {
				//do damge
				living->doDamage(damage);
			}
		}
	}
}

void ObjectCollection::setDebug(bool _debug) {
	debug = _debug;
}
