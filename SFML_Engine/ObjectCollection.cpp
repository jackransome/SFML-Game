#include "ObjectCollection.h"
#include "CollisionDetection.h"

ObjectCollection::ObjectCollection() {}

ObjectCollection::ObjectCollection(Console* _pConsole, InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera, b2World* _pPhysicsWorld) {
	pConsole = _pConsole;
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	pSoundPlayer = _pSoundPlayer;
	pCamera = _pCamera;
	pPhysicsWorld = _pPhysicsWorld;
	debug = false;
}

void ObjectCollection::draw() {
	if (!debug) {
		for (int i = 0; i < objects.size(); i++) {
			if (CollisionDetection::getDistance(pCamera->getPosition(), objects[i]->getCenter()) < 2000) {
				objects[i]->draw();
			}
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
	for (int i = 0; i < projectiles.size(); i++) {
		projectiles[i]->draw();
	}
}

void ObjectCollection::update() {
	Miner* tempM;
	AutoTurret* tempA;
	Enemy* tempE;
	Mineable* tempM2;

	for (int i = 0; i < objects.size(); i++) {
		//if rover
		if ((dynamic_cast<Rover*>(objects[i]))) {
			pullToPoint(objects[i]->getCenter().x, objects[i]->getCenter().y, 300);
		}
	}
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getPickedUp()) {
			Pickuper* tempP = dynamic_cast<Pickuper*>(getObjectById(objects[i]->getPickedUpById()));
			objects[i]->setCenter(tempP->getPickupPos());
			objects[i]->setRotation(tempP->getDropRotation());
		}
		if (objects[i]->getToDestroy()) {
			if (objects[i]->getControlled()) {
				controlledDead = true;
			}
			delete objects[i];
			objects.erase(objects.begin() + i);
			i--;
			continue;
		}
		//if can mine and is mining, get the mining point and check other objects for mineable and then if the point overlaps with them, 
		if ((tempM = dynamic_cast<Miner*>(objects[i]))) {
			if (tempM->getIsMining()) {
				for (int j = 0; j < objects.size(); j++) {
					if ((tempM2 = dynamic_cast<Mineable*>(objects[j])) && CollisionDetection::pointRectangleIntersect(tempM->getMinePoint(), objects[j]->getBoundingBoxPointer())) {
						tempM2->mine(tempM->getStrength());
						if (rand() % 100 > 95 || frame % 20 == 0) {
							pSoundPlayer->playSoundByName("mine_hit_1", 0.12);
							pConsole->addCommand(commandShakeScreen, 1.5f);
						}
						if (tempM2->getFullyMined()) {
							objects[j]->setToDestroy(true);
							addScapMetalDrop(objects[j]->getBoundingBox().x, objects[j]->getBoundingBox().y);
							pSoundPlayer->playSoundByName("mine_hit_1", 0.3);
							pConsole->addCommand(commandShakeScreen, 10.0f);
						}
					}
				}
			}
		}
		//if autoturret
		if ((tempA = dynamic_cast<AutoTurret*>(objects[i]))) {

			glm::vec2 target = getTarget(objects[i]->getCenter(), dynamic_cast<Living*>(objects[i])->getFaction());
			if (CollisionDetection::getDistance(target, objects[i]->getCenter()) < tempA->getTargetingRange()) {
				tempA->setTarget(target.x, target.y);
			}
			else {
				tempA->RemoveTarget();
			}
		}
		//if enemy
		if ((tempE = dynamic_cast<Enemy*>(objects[i]))) {

			glm::vec2 target = getTarget(objects[i]->getCenter(), dynamic_cast<Living*>(objects[i])->getFaction());
			if (CollisionDetection::getDistance(target, objects[i]->getCenter()) < tempE->getTargetingRange()) {
				tempE->setTarget(target.x, target.y);
			}
			else {
				tempE->RemoveTarget();
			}
		}
		objects[i]->update();
	}
	Living* living;
	bool hit;
	for (int i = 0; i < projectiles.size(); i++) {
		if (projectiles[i]->toDelete) {
			projectiles.erase(projectiles.begin() + i);
			i--;
			continue;
		}
		hit = false;
		projectiles[i]->run();
		for (int j = 0; j < objects.size(); j++) {
			if (objects[j]->getId() != projectiles[i]->getFromID()) {
				if (CollisionDetection::lineRectCollision(projectiles[i]->getLastPosition(), projectiles[i]->getPosition(), objects[j]->getBoundingBoxPointer())) {
					projectiles[i]->setPosition(CollisionDetection::getLineRectCollision(projectiles[i]->getLastPosition(), projectiles[i]->getPosition(), objects[j]->getBoundingBoxPointer()));
					hit = true;
				}
			}
		}
		if (hit) {
			pConsole->addCommand(commandDoAEODamage, projectiles[i]->getPosition().x, projectiles[i]->getPosition().y, 50, 10, projectiles[i]->getFromID());
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
	}
	frame++;
}

void ObjectCollection::addMainCharacter(float x, float y) {
	objects.push_back(new MainCharacter(pInputManager, pSpriteCollection, x, y, pPhysicsWorld));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addFootPrint(float x, float y) {
	objects.push_back(new FootPrint(pSpriteCollection, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addRoverTracks(float x, float y, float rotation){
	objects.push_back(new RoverTracks(pSpriteCollection, x, y, rotation));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addAction1Animation(float x, float y) {
	objects.push_back(new Action1Animation(pSpriteCollection, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addWall(int x, int y, int w, int h) {
	objects.push_back(new Wall(pSpriteCollection, x, y, w, h, pPhysicsWorld));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addEnemy(int x, int y) {
	objects.push_back(new Enemy(pSpriteCollection, pSoundPlayer, x, y, pPhysicsWorld));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addRover(int x, int y){
	objects.push_back(new Rover(pInputManager, pSpriteCollection, pSoundPlayer, x, y, pPhysicsWorld));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addCrate(int x, int y){
	objects.push_back(new Crate(pSpriteCollection, x, y, pPhysicsWorld));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addRelay(int x, int y){
	objects.push_back(new Relay(pSpriteCollection, pConsole, pSoundPlayer, x, y, pPhysicsWorld));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addScapMetalPile(int x, int y){
	objects.push_back(new ScrapMetalPile(pSpriteCollection, x, y, pPhysicsWorld));
	objects[objects.size() - 1]->setRotation((rand() % 360));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addScapMetalDrop(int x, int y) {
	objects.push_back(new ScrapMetalDrop(pSpriteCollection, x, y, pPhysicsWorld));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addMarketRelay(int x, int y){
	objects.push_back(new MarketRelay(pSpriteCollection, pInputManager, pConsole, pSoundPlayer, x, y, pPhysicsWorld));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addAutoTurret(int x, int y){
	objects.push_back(new AutoTurret(pSpriteCollection, pConsole, x, y, pPhysicsWorld));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addProjectile(float _x, float _y, float _rotation, float _speed, int _fromID){
	projectiles.push_back(new Projectile(pSpriteCollection, _x, _y, _rotation, _speed, _fromID));
}

void ObjectCollection::setLatestId() {
	objects[objects.size() - 1]->setId(nextId);
	nextId++; //when is this gonna overflow
}

void ObjectCollection::setLatestConsole() {
	objects[objects.size() - 1]->setConsolePointer(pConsole);
}

void ObjectCollection::runCollisionDetection() {
	pPhysicsWorld->Step(1.0f / 60.0f , 100, 50);
	for (int i = 0; i < objects.size(); i++) {
		if (!objects[i]->getPickedUp() && objects[i]->getCollidability() == movable) {
			for (int j = 0; j < objects.size(); j++) {
				if (i != j && !objects[j]->getPickedUp() && objects[j]->getCollidability() == movable && objects[j]->getCollidability() > objects[i]->getCollidability()) {
					//CollisionDetection::correctPositionBoth(objects[j]->getBoundingBoxPointer(), objects[i]->getBoundingBoxPointer());
				}
			}
		}
	}
	for (int i = 0; i < objects.size(); i++) {
		if (!objects[i]->getPickedUp() && objects[i]->getCollidability() < movable) {
			for (int j = 0; j < objects.size(); j++) {
				if (i != j && !objects[j]->getPickedUp() && objects[j]->getCollidability() < 3 && objects[j]->getCollidability() > objects[i]->getCollidability()) {
					//CollisionDetection::correctPosition(objects[j]->getBoundingBoxPointer(), objects[i]->getBoundingBoxPointer());
				}
			}
		}
	}
}

void ObjectCollection::drawHealthBars() {
	Living* living;
	for (int i = 0; i < objects.size(); i++) {
		//check if object inherits livings
		if (living = dynamic_cast<Living*>(objects[i])) {
			pSpriteCollection->addRectDraw(objects[i]->getCenter().x - 30, objects[i]->getBoundingBox().y - 30, 60*(living->getHealth()/living->getMaxHealth()), 5, 1000000, sf::Color(0, 255, 0, 10));
		}
	}
}

void ObjectCollection::doAEODamage(float x, float y, float range, float damage, int id) {
	Living* living;
	for (int i = 0; i < objects.size(); i++) {
		//check if object inherits living
		if (objects[i]->getId() != id && (living = dynamic_cast<Living*>(objects[i])) && !objects[i]->getPickedUp()) {
			//check if within range
			/*if (i == 0) {
				std::cout << "obj: " << objects[i]->getBoundingBox().x + (objects[i]->getBoundingBox().w / 2) << "|" << objects[i]->getBoundingBox().y + (objects[i]->getBoundingBox().h / 2) << "|\n";
				std::cout << "mouse: " << x << "|" << y << "|\n";
				std::cout << "|" << (objects[i]->getBoundingBox().x + (objects[i]->getBoundingBox().w / 2)) - x << "|" << (objects[i]->getBoundingBox().x + (objects[i]->getBoundingBox().h / 2)) - y << "|\n";
			}*/
			if (pow((objects[i]->getBoundingBox().x + (objects[i]->getBoundingBox().w / 2)) - x, 2) + pow((objects[i]->getBoundingBox().y + (objects[i]->getBoundingBox().h / 2)) - y, 2) < pow(range, 2)) {
				//do damage
				living->doDamage(damage);
				if (living->getHealth() <= 0) {
					objects[i]->setToDestroy(true);
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
		if (objects[i]->getType() == objectEnemy) {
			dynamic_cast<Enemy*>(objects[i])->setTarget(x, y);
		}
	}
}

glm::vec2 ObjectCollection::getTarget(glm::vec2 position, FactionIdentifier faction){
	FactionIdentifier targetFaction;
	if (faction == factionFriendly) {
		targetFaction = factionHostile;
	} else if (faction == factionHostile) {
		targetFaction = factionFriendly;
	}
	int minDistance = 10000;
	int minIndex = -1;
	for (int j = 0; j < objects.size(); j++) {
		if (dynamic_cast<Living*>(objects[j]) && dynamic_cast<Living*>(objects[j])->getFaction() == targetFaction && CollisionDetection::getDistance(position, objects[j]->getCenter()) < minDistance) {
			minDistance = CollisionDetection::getDistance(position, objects[j]->getCenter());
			minIndex = j;
		}
	}
	if (minIndex == -1) {
		//std::cout << "NOTHING TO TARGET\n";
		return glm::vec2(100000,100000);
	}
	return objects[minIndex]->getCenter() + glm::vec2(objects[minIndex]->getBoundingBox().xv*5, objects[minIndex]->getBoundingBox().yv*5);
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

void ObjectCollection::runPickUp(int id){
	Object* object = getObjectById(id);
	if (object == nullptr) {
		return;
	}
	Pickuper* pickuper;
	if (!(pickuper = dynamic_cast<Pickuper*>(object))) {
		std::cout << "OBJECT WITH ID " << id << " NOT A PICKUPER\n";
		return;
	}
	if (pickuper->getHolding()) {
		std::cout << "OBJECT WITH ID " << id << " ALREADY HOLDING SOMETHING\n";
		return;
	}
	glm::vec2 pickupPos = pickuper->getPickupPos();
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getCanBePickedUp()) {
			if (CollisionDetection::getDistance(pickupPos, objects[i]->getCenter()) < 30){//} CollisionDetection::pointRectangleIntersect(pickupPos, objects[i]->getBoundingBoxPointer())) {
				objects[i]->setPickedUp(true);
				objects[i]->setPickedUpById(id);
				pickuper->setTypeHeld(objects[i]->getType());
				pickuper->setIdHeld(objects[i]->getId());
				return;
			}
		}
	}
}

void ObjectCollection::runDrop(int id) {
	Object* object = getObjectById(id);
	if (object == nullptr) {
		return;
	}
	Pickuper* pickuper;
	if (!(pickuper = dynamic_cast<Pickuper*>(object))) {
		std::cout << "OBJECT WITH ID " << id << " NOT A PICKUPER\n";
		return;
	}
	if (!pickuper->getHolding()) {
		std::cout << "OBJECT WITH ID " << id << " NOT HOLDING ANYTHING\n";
		return;
	}
	object = getObjectById(pickuper->getIdHeld());
	if (object == nullptr) {
		return;
	}
	object->setPickedUp(false);
	object->setCenter(pickuper->getPickupPos());
	object->setRotation(pickuper->getDropRotation());
	pickuper->drop();
}

int ObjectCollection::getClosestControllable(int currentID){
	int mouseX = pInputManager->translatedMouseX;
	int mouseY = pInputManager->translatedMouseY;
	Object* current = getObjectById(currentID);
	if (current == nullptr) {
		std::cout << "current object does not exist\n";
		return -1;
	}
	int currentX = current->getBoundingBox().x;
	int currentY = current->getBoundingBox().y;
	Controllable* controllable;
	if (!(controllable = dynamic_cast<Controllable*>(current))) {
		std::cout << "current object given is not controllable\n";
	}
	int range = controllable->getRange();
	int closestDistance = 100000;
	int distanceFromCurrent = 0;
	int distanceFromMouse = 0;
	int closestID = -1;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() != currentID && (controllable = dynamic_cast<Controllable*>(objects[i]))) {
			//if another object is found that is controllable and not the current object
			//get distance, see if its within range
			distanceFromCurrent = CollisionDetection::getDistance(glm::vec2(currentX, currentY), glm::vec2(objects[i]->getBoundingBox().x, objects[i]->getBoundingBox().y));
			distanceFromMouse = CollisionDetection::getDistance(glm::vec2(mouseX, mouseY), glm::vec2(objects[i]->getBoundingBox().x, objects[i]->getBoundingBox().y));
			if (distanceFromCurrent < range && distanceFromMouse < closestDistance) {
				//if closest so far, record distance and the id of that object
				closestDistance = distanceFromMouse;
				closestID = objects[i]->getId();
			}
		}
	}
	return closestID;
}

void ObjectCollection::pullToPoint(float x, float y, int range){
	glm::vec2 direction;
	float distance;
	for (int i = 0; i < objects.size(); i++) {
		if (dynamic_cast<ScrapMetalDrop*>(objects[i])) {
			direction.x = x - objects[i]->getBoundingBox().x;
			direction.y = y - objects[i]->getBoundingBox().y;
			distance = sqrt(direction.x * direction.x + direction.y * direction.y);
			if (distance < range) {
				direction /= (distance * distance);
				direction *= range;
				objects[i]->getPhysicsBody()->ApplyForceToCenter(b2Vec2(direction.x*10000, direction.y*10000), true);
				//objects[i]->push(direction.x, direction.y);
			}

		}
	}
}

void ObjectCollection::sellObjects(float startX, float startY, float w, float h, int marketRelayID){
	BoundingBox temp;
	temp.x = startX;
	temp.y = startY;
	temp.w = w;
	temp.h = h;
	int credits = 0;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getSellable() && CollisionDetection::pointRectangleIntersect(objects[i]->getCenter(), &temp)){
			objects[i]->setToDestroy(true);
			credits += 1;
		}
	}
	dynamic_cast<MarketRelay*>(getObjectById(marketRelayID))->addCredit(credits);
}

Object* ObjectCollection::getObjectById(int id)
{
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getId() == id) {
			return objects[i];
		}
	}
	std::cout << "OBJECT WITH ID " << id << " NOT FOUND\n";
	return nullptr;
}

bool ObjectCollection::getControlledDead(){
	return controlledDead;
}
