#include "ObjectCollection.h"
#include "CollisionDetection.h"

ObjectCollection::ObjectCollection() {}

ObjectCollection::ObjectCollection(Console* _pConsole, InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera) {
	pConsole = _pConsole;
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	pSoundPlayer = _pSoundPlayer;
	pCamera = _pCamera;
	debug = false;
}

void ObjectCollection::draw() {
	if (!debug) {
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->draw();
			if (objects[i]->getId() == cameraFocusId) {
				pCamera->setPosition(objects[i]->getCenter());
			}
		}
	}
	else {
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->draw();
			pSpriteCollection->addRectDraw(objects[i]->getBoundingBox().x, objects[i]->getBoundingBox().y, objects[i]->getBoundingBox().w, objects[i]->getBoundingBox().h, 10000, sf::Color(0, 255, 0, 100));
			pSpriteCollection->addCircleDraw(objects[i]->getCenter().x - 3, objects[i]->getCenter().y - 3, 3, 100000, sf::Color(255, 255, 255, 2000));
			if (objects[i]->getId() == cameraFocusId) {
				pCamera->setPosition(objects[i]->getCenter());
			}
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

void ObjectCollection::addRover(int x, int y){
	objects.push_back(new Rover(pInputManager, pSpriteCollection, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addCrate(int x, int y){
	objects.push_back(new Crate(pSpriteCollection, x, y));
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
			pSpriteCollection->addRectDraw(objects[i]->getBoundingBox().x, objects[i]->getBoundingBox().y - 30, living->getHealth(), 5, -10000, sf::Color(0, 255, 0));
		}
	}
}

void ObjectCollection::doAEODamage(float x, float y, float range, float damage) {
	Living* living;
	for (int i = 0; i < objects.size(); i++) {
		//check if object inherits living
		if (living = dynamic_cast<Living*>(objects[i])) {
			//check if within range
			if (i == 0) {
				std::cout << "obj: " << objects[i]->getBoundingBox().x + (objects[i]->getBoundingBox().w / 2) << "|" << objects[i]->getBoundingBox().y + (objects[i]->getBoundingBox().h / 2) << "|\n";
				std::cout << "mouse: " << x << "|" << y << "|\n";
				std::cout << "|" << (objects[i]->getBoundingBox().x + (objects[i]->getBoundingBox().w / 2)) - x << "|" << (objects[i]->getBoundingBox().x + (objects[i]->getBoundingBox().h / 2)) - y << "|\n";
			}
			if (pow((objects[i]->getBoundingBox().x + (objects[i]->getBoundingBox().w / 2)) - x, 2) + pow((objects[i]->getBoundingBox().y + (objects[i]->getBoundingBox().h / 2)) - y, 2) < pow(range, 2)) {
				//do damage
				living->doDamage(damage);
				if (living->getHealth() <= 0) {
					objects.erase(objects.begin() + i);
					i--;
				}
			}
		}
	}
}

void ObjectCollection::setDebug(bool _debug) {
	debug = _debug;
}

void ObjectCollection::setEnemyTarget(int x, int y){
	for (int i = 0; i < objects.size(); i++) {
		//check if object inherits living
		if (objects[i]->getType() == 2) {
			dynamic_cast<Enemy*>(objects[i])->setTarget(x, y);
		}
	}
}

void ObjectCollection::setCameraFocus(int id){
	cameraFocusId = id;
}

void ObjectCollection::setControls(int _id, bool _controlled){
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == _id) {
			objects[i]->setControlled(_controlled);
			break;
		}
	}
}

void ObjectCollection::resetAllControls(){
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->setControlled(false);
	}
}
