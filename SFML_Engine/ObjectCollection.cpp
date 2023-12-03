#include "ObjectCollection.h"
#include "CollisionDetection.h"
#include <cstdlib>  // For rand() and RAND_MAX
#include <chrono>

ObjectCollection::ObjectCollection() {}

ObjectCollection::ObjectCollection(Console* _pConsole, InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera, Inventory* _pinventory) {
	pConsole = _pConsole;
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	pSoundPlayer = _pSoundPlayer;
	pCamera = _pCamera;
	debug = false;
	pInventory = _pinventory;
}

void ObjectCollection::draw() {
	if (!debug) {
		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->getType() == objectFootprint) {
				int e = 0;
			}
			if (CollisionDetection::getDistance(pCamera->getPosition(), objects[i]->getCenter()) < 2000) {
				if (objects[i]->getToBuild()) {
					objects[i]->drawBuilding();
				}
				else {
					objects[i]->draw();
				}
				
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
	for (int i = 0; i < numBeamsToDraw; i++) {
		pSpriteCollection->drawBeamLight(glm::vec2(beamsToDraw[i].r, beamsToDraw[i].g), glm::vec2(beamsToDraw[i].b, beamsToDraw[i].a), glm::vec3(255, 255, 255), 1, 2);
	}
	//inventory test drawing:
	pSpriteCollection->setAbsoluteMode(true);
	pSpriteCollection->addTextDraw(1, 50, 50, 1000000, std::to_string(pInventory->getResources(Resource::scrap)), 40, sf::Color(255, 255, 255, 255));
	pSpriteCollection->addTextDraw(1, 50, 100, 1000000, std::to_string(pInventory->getResources(Resource::component)), 40, sf::Color(255, 255, 255, 255));
	pSpriteCollection->setAbsoluteMode(false);
	
	numBeamsToDraw = 0;
}

void ObjectCollection::update() {
	Miner* tempM;
	AutoTurret* tempA;
	Enemy* tempE;
	EnemyBombRover* tempB;
	Mineable* tempM2;
	Pickuper* tempP;
	Object* tempOb;

	//for (int i = 0; i < objects.size(); i++) {
	//	//if rover
	//	if ((dynamic_cast<Rover*>(objects[i]))) {
	//		pullToPoint(objects[i]->getCenter().x, objects[i]->getCenter().y, 300);
	//	}
	//}
	for (int i = 0; i < objects.size(); i++) {
		for (int j = 0; j < objects.size(); j++) {
			if (i != j) {
				runCollisionDetection(objects[i], objects[j]);
			}
		}
		if (objects[i]->getToBuild()) {
			for (int j = 0; j < objects.size(); j++) {
				if (objects[j]->getType() == objectBuildDrone){
					BuildDrone* drone = dynamic_cast<BuildDrone*>(objects[j]);
					if (!drone->getHasTarget()) {
						drone->setTarget(objects[i]);
					}
				}
			}
			//objects[i]->incrementBuildProgress(0.01);
		}
		else {
			if (objects[i]->getPickedUp()) {
				tempOb = getObjectById(objects[i]->getPickedUpById());
				if (tempOb == nullptr) {
					//DROP
					runDropWithoutPickuper(objects[i]->getId());
				}
				else {
					tempP = dynamic_cast<Pickuper*>(tempOb);
					objects[i]->setCenter(tempP->getPickupPos());
					objects[i]->setRotation(tempP->getDropRotation());
				}
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

				glm::vec4 target = getTarget(objects[i]->getCenter(), dynamic_cast<Living*>(objects[i])->getFaction());
				if (CollisionDetection::getDistance(target, objects[i]->getCenter()) < tempA->getTargetingRange()) {
					tempA->setTarget(target.x, target.y, target.z, target.w);
				}
				else {
					tempA->RemoveTarget();
				}
			}
			//if enemy
			else if ((tempE = dynamic_cast<Enemy*>(objects[i]))) {
				glm::vec4 target = getTarget(objects[i]->getCenter(), dynamic_cast<Living*>(objects[i])->getFaction());
				if (CollisionDetection::getDistance(target, objects[i]->getCenter()) < tempE->getTargetingRange()) {
					tempE->setTarget(target.x, target.y, target.z, target.w);
				}
				else {
					tempE->RemoveTarget();
				}
			}

			else if ((tempB = dynamic_cast<EnemyBombRover*>(objects[i]))) {
				glm::vec4 target = getTarget(objects[i]->getCenter(), dynamic_cast<Living*>(objects[i])->getFaction());
				if (CollisionDetection::getDistance(target, objects[i]->getCenter()) < tempB->getTargetingRange()) {
					tempB->setTarget(target.x, target.y);
				}
				else {
					tempB->RemoveTarget();
				}
			}
			objects[i]->update();
		}

	}
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getToDestroy()) {
			if (objects[i]->getControlled()) {
				controlledDead = true;
			}
			if (objects[i]->getPickedUp()) {
				tempOb = getObjectById(objects[i]->getPickedUpById());
				tempP = dynamic_cast<Pickuper*>(tempOb);
				tempP->drop();
			}
			freeObjectMemory(i);
			objects.erase(objects.begin() + i);
			i--;
			continue;
		}
	}
	Living* living;
	bool hit;
	for (int i = 0; i < projectiles.size(); i++) {
		if (projectiles[i]->toDelete) {
			projectiles.erase(projectiles.begin() + i);
			i--;
			continue;
		}
		projectiles[i]->run();
		
		hit = false;
		
		for (int j = 0; j < objects.size(); j++) {
			if (objects[j]->getId() != projectiles[i]->getFromID() && objects[j]->getType() != objectScrapMetalDrop && objects[j]->getType() != objectBuildDrone) {
				if (CollisionDetection::lineRectCollision(projectiles[i]->getLastPosition(), projectiles[i]->getPosition(), objects[j]->getBoundingBoxPointer())) {
					projectiles[i]->setPosition(CollisionDetection::getLineRectCollision(projectiles[i]->getLastPosition(), projectiles[i]->getPosition(), objects[j]->getBoundingBoxPointer()));
					hit = true;

				}
			}
		}
		if (hit) {
			glm::vec2 distVector = pConsole->getControlPosition() - projectiles[i]->getPosition();
			float distance = sqrt(distVector.x * distVector.x + distVector.y * distVector.y);
			pConsole->addCommand(commandPlaySound, "laser_impact", 0.2 / (1 + distance / 100));
			pConsole->addCommand(commandDoAEODamage, projectiles[i]->getPosition().x, projectiles[i]->getPosition().y, 50, 10, projectiles[i]->getFromID());
			projectiles[i]->toDelete = true;
		}
	}
	for (int i = 0; i < numBeams; i++) {
		bool hit = false;
		glm::vec2 start = glm::vec2(beams[i].r, beams[i].g);
		glm::vec2 end = glm::vec2(beams[i].b, beams[i].a);
		for (int j = 0; j < objects.size(); j++) {
			if (objects[j]->getId() != beamsFrom[i] && objects[j]->getType() != objectScrapMetalDrop && objects[j]->getType() != objectBuildDrone && CollisionDetection::lineRectCollision(start, end, objects[j]->getBoundingBoxPointer())) {
				end = CollisionDetection::getLineRectCollision(start, end, objects[j]->getBoundingBoxPointer());
				beams[i].b = end.x;
				beams[i].a = end.y;
				hit = true;
			}
		}
		if (hit) {
			pConsole->addCommand(commandDoAEODamage, end.x, end.y, 30, 2, beamsFrom[i]);
		}
	}
	if (numBeams) {
		beamsToDraw = beams;
		numBeamsToDraw = numBeams;
		numBeams = 0;
	}

	frame++;
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

void ObjectCollection::addSmoke(float x, float y, float height, float scale){
	objects.push_back(new Smoke(pSpriteCollection, x, y, height, scale));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addExplosion(float x, float y, float size) {
	objects.push_back(new Explosion(pSpriteCollection, pConsole, pSoundPlayer, x, y, size));
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
	objects.push_back(new Wall(pSpriteCollection, x, y, w, h));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addEnemy(int x, int y) {
	objects.push_back(new Enemy(pSpriteCollection, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addRover(int x, int y){
	objects.push_back(new Rover(pInputManager, pSpriteCollection, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addCrate(int x, int y){
	objects.push_back(new Crate(pSpriteCollection, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addRelay(int x, int y){
	objects.push_back(new Relay(pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addScapMetalPile(int x, int y){
	objects.push_back(new ScrapMetalPile(pSpriteCollection, x, y));
	objects[objects.size() - 1]->setRotation((rand() % 360));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addScapMetalDrop(int x, int y) {
	objects.push_back(new ScrapMetalDrop(pSpriteCollection, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addMarketRelay(int x, int y){
	objects.push_back(new MarketRelay(pSpriteCollection, pInputManager, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addAutoTurret(int x, int y){
	objects.push_back(new AutoTurret(pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addJammer(int x, int y){
	objects.push_back(new Jammer(pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addDefenseOrb(int x, int y){
	objects.push_back(new DefenseOrb(pInputManager, pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addBuildDrone(int x, int y){
	objects.push_back(new BuildDrone(pSpriteCollection, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addSpark(int x, int y, int height){
	objects.push_back(new Spark(pSpriteCollection, glm::vec3(x, y, height), glm::vec3(((double)rand() / (RAND_MAX))*3 - 1.5, ((double)rand() / (RAND_MAX))*1.5, ((double)rand() / (RAND_MAX))*2), ((double)rand() / (RAND_MAX))*3.5 + 0.5));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addGenerator(int x, int y){
	objects.push_back(new Generator(pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addEnemyBombRover(int x, int y){
	objects.push_back(new EnemyBombRover(pSpriteCollection, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addProjectile(float _x, float _y, float _rotation, float _speed, int _fromID){
	projectiles.push_back(new Projectile(pSpriteCollection, _x, _y, _rotation, _speed, _fromID));
}

void ObjectCollection::addBeam(float _x1, float _y1, float _x2, float _y2, int _fromID){
	if (numBeams >= maxBeams) {
		std::cout << "MAX BEAMS REACHED\n";
	}
	beams[numBeams] = glm::vec4(_x1, _y1, _x2, _y2);
	beamsFrom[numBeams] = _fromID;
	numBeams++;
}

void ObjectCollection::setLatestId() {
	objects[objects.size() - 1]->setId(nextId);
	nextId++; //when is this gonna overflow
}

void ObjectCollection::setLatestConsole() {
	objects[objects.size() - 1]->setConsolePointer(pConsole);
}

void ObjectCollection::runCollisionDetection(Object* o1, Object* o2) {

	if(o1->getCollidability() == movable) {
		if (!o2->getPickedUp() && o2->getCollidability() == movable) {
			if (o2->getCollidability() > o1->getCollidability()) {
				CollisionDetection::correctPosition(o2->getBoundingBoxPointer(), o1->getBoundingBoxPointer());
			}
			else {
				CollisionDetection::correctPositionBoth(o2->getBoundingBoxPointer(), o1->getBoundingBoxPointer());
			}
		}

	}
	if (o1->getCollidability() == controllable) {
		if (o1->getId() == cameraFocusId && o2->getType() == objectScrapMetalDrop && CollisionDetection::CheckRectangleIntersect(o1->getBoundingBoxPointer(), o2->getBoundingBoxPointer())) {
			pInventory->addResources(Resource::scrap, 1);
			o2->setToDestroy(true);
		}
		if (o2->getCollidability() == controllable) {
			CollisionDetection::correctPositionBoth(o2->getBoundingBoxPointer(), o1->getBoundingBoxPointer());
		}
	}
	if (o1->getCollidability() < movable) {
		if (!o2->getPickedUp() && o2->getCollidability() < 3 && o2->getCollidability() > o1->getCollidability()) {
			CollisionDetection::correctPosition(o2->getBoundingBoxPointer(), o1->getBoundingBoxPointer());
		}
	}
	if (o1->getCollidability() == droneCol && o2->getCollidability() == droneCol) {
		if (CollisionDetection::CheckRectangleIntersect(o2->getBoundingBoxPointer(), o1->getBoundingBoxPointer())) {
			CollisionDetection::correctPosition(o2->getBoundingBoxPointer(), o1->getBoundingBoxPointer());
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

void ObjectCollection::setEnemyTarget(int x, int y, float xv, float yv){
	for (int i = 0; i < objects.size(); i++) {
		//check if object inherits living
		if (objects[i]->getType() == objectEnemy) {
			dynamic_cast<Enemy*>(objects[i])->setTarget(x, y, xv, yv);
		}
	}
}

glm::vec4 ObjectCollection::getTarget(glm::vec2 position, FactionIdentifier faction) {
	FactionIdentifier targetFaction = (faction == factionFriendly) ? factionHostile : factionFriendly;

	int minDistance = 10000;
	int minIndex = -1;
	int objectsSize = objects.size(); // Store size if not changing in the loop
	
	for (int j = 0; j < objectsSize; j++) {

		if (objects[j]->getLiving()) {
			if ((targetFaction == factionHostile && objects[j]->getIsEnemy()) || (targetFaction == factionFriendly && !objects[j]->getIsEnemy())) {

				int distance = CollisionDetection::getDistance(position, objects[j]->getCenter());

				if (distance < minDistance) {
					minDistance = distance;
					minIndex = j;
				}
			}
		}
	}
	if (minIndex == -1) {
		return glm::vec4(100000, 100000, 0, 0);
	}

	auto& targetObject = objects[minIndex];
	glm::vec2 tempPos = targetObject->getCenter() + glm::vec2(targetObject->getBoundingBox().xv * 5, targetObject->getBoundingBox().yv * 5);
	return glm::vec4(tempPos.x, tempPos.y, targetObject->getBoundingBox().xv, targetObject->getBoundingBox().yv);
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
	pickuper->drop();
	if (object == nullptr) {
		return;
	}
	object->setPickedUp(false);
	object->setCenter(pickuper->getPickupPos());
	object->setRotation(pickuper->getDropRotation());
	pickuper->drop();
}

void ObjectCollection::runDropWithoutPickuper(int id) {
	Object* object = getObjectById(id);
	if (object == nullptr) {
		std::cout << "OBJECT WITH ID " << id << " NOT FOUND\n";
		return;
	}

	object->setPickedUp(false);
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
				//direction /= (distance);
				//float speed = sqrt(vel.x * vel.x + vel.y * vel.y);
				//direction *= speed;
				//direction = glm::vec2(vel.x * 0.7 + direction.x * 0.3, vel.y * 0.7 + direction.y * 0.3);

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
	//std::cout << "OBJECT WITH ID " << id << " NOT FOUND\n";
	return nullptr;
}

void ObjectCollection::setControlledDead(bool cd){
	controlledDead = cd;
}

bool ObjectCollection::getControlledDead(){
	return controlledDead;
}

void ObjectCollection::clear(){
	controlledDead = true;
	for (int i = 0; i < objects.size(); i++) {
		freeObjectMemory(i);
	}
	objects.clear();
	nextId = 0;
}

void ObjectCollection::AddToInventory(Resource resource, int amount){
	pInventory->addResources(resource, amount);
}

void ObjectCollection::setLastToBuild(){
	objects[objects.size() - 1]->setToBuild(true);
}

void ObjectCollection::freeObjectMemory(int index) {
	switch (objects[index]->getType()) {
	case objectCrate:
		delete dynamic_cast<Crate*>(objects[index]);
		break;
	case objectFootprint:
		delete dynamic_cast<FootPrint*>(objects[index]);
		break;
	case objectRoverTracks:
		delete dynamic_cast<RoverTracks*>(objects[index]);
		break;
	case objectRover:
		delete dynamic_cast<Rover*>(objects[index]);
		break;
	case objectMainCharacter:
		delete dynamic_cast<MainCharacter*>(objects[index]);
		break;
	case objectRelay:
		delete dynamic_cast<Relay*>(objects[index]);
		break;
	case objectWall:
		delete dynamic_cast<Wall*>(objects[index]);
		break;
	case objectEnemy:
		delete dynamic_cast<Enemy*>(objects[index]);
		break;
	case objectScrapMetalDrop:
		delete dynamic_cast<ScrapMetalDrop*>(objects[index]);
		break;
	case objectScrapMetalPile:
		delete dynamic_cast<ScrapMetalPile*>(objects[index]);
		break;
	case objectAutoTurret:
		delete dynamic_cast<AutoTurret*>(objects[index]);
		break;
	case objectMarketRelay:
		delete dynamic_cast<MarketRelay*>(objects[index]);
		break;
	case objectDefenseOrb:
		delete dynamic_cast<DefenseOrb*>(objects[index]);
		break;
	case objectGenerator:
		delete dynamic_cast<Generator*>(objects[index]);
		break;
	case objectEnemyBombRover:
		delete dynamic_cast<EnemyBombRover*>(objects[index]);
		break;
	default:
		delete objects[index];
		break;
	}
}
