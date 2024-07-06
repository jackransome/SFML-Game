#include "ObjectCollection.h"
#include "CollisionDetection.h"
#include <cstdlib>  // For rand() and RAND_MAX
#include <chrono>
#include <memory>

ObjectCollection::ObjectCollection() {}

ObjectCollection::ObjectCollection(Console* _pConsole, InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera, Inventory* _pinventory) {
	pConsole = _pConsole;
	pInputManager = _pInputManager;
	pSpriteCollection = _pSpriteCollection;
	pSoundPlayer = _pSoundPlayer;
	pCamera = _pCamera;
	debug = false;
	pInventory = _pinventory;
	// Initialize the map with zero counts for each command
	for (int i = 0; i < object_count; ++i) {
		objectCounter[static_cast<ObjectType>(i)] = 0;
	}
}

void ObjectCollection::draw() {
	if (!debug) {
		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->getType() == objectSpark) {
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
	pSpriteCollection->addTextDraw(2, 50, 400, 1000000, std::to_string(pInventory->getResources(Resource::scrap)), 14, sf::Color(255, 255, 255, 255));
	pSpriteCollection->addTextDraw(2, 106, 400, 1000000, std::to_string(pInventory->getResources(Resource::component)), 14, sf::Color(255, 255, 255, 255));
	pSpriteCollection->setAbsoluteMode(false);
	
	numBeamsToDraw = 0;
}

void ObjectCollection::update() {
	std::shared_ptr <Miner> tempM;
	std::shared_ptr <AutoTurret> tempA;
	std::shared_ptr <Enemy> tempE;
	std::shared_ptr <EnemyBombRover> tempB;
	std::shared_ptr <Mineable> tempM2;
	std::shared_ptr <Pickuper> tempP;
	std::shared_ptr<Object> tempOb;
	std::shared_ptr<Relay> tempR;
	std::shared_ptr <EnemyTurretRover> tempT;
	std::shared_ptr<TeleporterPillar> tempTP;

	//for (int i = 0; i < objects.size(); i++) {
	//	//if rover
	//	if ((dynamic_cast<Rover*>(objects[i]))) {
	//		pullToPoint(objects[i]->getCenter().x, objects[i]->getCenter().y, 300);
	//	}
	//}

	for (int i = 0; i < objects.size(); i++) {
		if (!objects[i]->getToBuild() && objects[i]->getJustBuilt()) {
			
			changeObjectCount(objects[i]->getType(), 1);

			objects[i]->resetJustBuilt();

			if (objects[i]->getType() == objectGenerator) {
				generatorPos.x = objects[i]->getBoundingBoxPointer()->x;
				generatorPos.y = objects[i]->getBoundingBoxPointer()->y;
			}
		}
		for (int j = 0; j < objects.size(); j++) {
			if (i != j) {
				runCollisionDetection(*objects[i], *objects[j]);
			}
		}

		if (objects[i]->getToBuild()) {
			for (int j = 0; j < objects.size(); j++) {
				if (objects[j]->getType() == objectBuildDrone && !objects[j]->getToBuild()){
					auto drone = std::dynamic_pointer_cast<BuildDrone>(objects[j]);
					if (!drone->getHasTarget()) {
						drone->setTarget(objects[i]);
					}
				}
			}
			//objects[i]->incrementBuildProgress(0.01);
		}
		else {
			if (objects[i]->getIsPowerNode()) {
				std::dynamic_pointer_cast<PowerNode>(objects[i])->distribute();
			}
			if (objects[i]->getPickedUp()) {
				//if currently picked up, either drop if the object that picked you up is dead, or move with it accordingly
				tempOb = getObjectById(objects[i]->getPickedUpById());
				if (tempOb == nullptr) {
					//DROP
					runDropWithoutPickuper(objects[i]->getId());
				}
				else {
					tempP = std::dynamic_pointer_cast<Pickuper>(tempOb);
					objects[i]->setCenter(tempP->getPickupPos());
					objects[i]->setRotation(tempP->getDropRotation());
				}
			}
			//if can mine and is mining, get the mining point and check other objects for mineable and then if the point overlaps with them, 
			if ((tempM = std::dynamic_pointer_cast<Miner>(objects[i]))) {
				if (tempM->getIsMining()) {
					for (int j = 0; j < objects.size(); j++) {
						if ((tempM2 = std::dynamic_pointer_cast<Mineable>(objects[j])) && CollisionDetection::pointRectangleIntersect(tempM->getMinePoint(), objects[j]->getBoundingBoxPointer())) {
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
			if (objects[i]->getType() == objectAutoTurret && !objects[i]->getHasTarget()) {
				std::dynamic_pointer_cast<AutoTurret>(objects[i])->setTarget(getTarget(objects[i]->getCenter(), objects[i]->getFaction(), objects[i]->getTargetingRange()));
			}
			//if enemy drone
			else if (objects[i]->getType() == objectEnemy && !objects[i]->getHasTarget()) {
				std::dynamic_pointer_cast<Enemy>(objects[i])->setTarget(getTarget(objects[i]->getCenter(), objects[i]->getFaction(), objects[i]->getTargetingRange()));
			}
			//if enemy bomb rover
			else if (objects[i]->getType() == objectEnemyBombRover && !objects[i]->getHasTarget()) {
				std::dynamic_pointer_cast<EnemyBombRover>(objects[i])->setTarget(getTarget(objects[i]->getCenter(), objects[i]->getFaction(), objects[i]->getTargetingRange()));
			}
			//if enemy turret rover
			else if (objects[i]->getType() == objectEnemyTurretRover && !objects[i]->getHasTarget()) {
				std::dynamic_pointer_cast<EnemyTurretRover>(objects[i])->setTarget(getTarget(objects[i]->getCenter(), objects[i]->getFaction(), objects[i]->getTargetingRange()));
			}
			else if ((tempTP = std::dynamic_pointer_cast<TeleporterPillar>(objects[i])) && objects[i]->getFullyCharged()) {
				int counter = 0;
				int index1;
				for (int j = 0; j < objects.size(); j++) {
					if (j != i && !objects[j]->getToBuild() && objects[j]->getType() == objectTeleporterPillar && objects[j]->getFullyCharged()) {
						if (counter == 0) {
							counter++;
							index1 = j;

						}
						else {
							counter++;
							tempTP->setActive(true);
							if (!teleporterExists) {
								glm::vec2 teleporterPos = (objects[j]->getCenter() + objects[i]->getCenter() + objects[index1]->getCenter());
								teleporterPos.x *= 1.0 / 3.0;
								teleporterPos.y *= 1.0 / 3.0;
								addTeleporter(teleporterPos.x, teleporterPos.y);
								teleporterExists = true;
								pConsole->addCommand(commandPlaySound, "alarm_1", pSoundPlayer->getSpatialVolume(teleporterPos, pConsole->getControlPosition()));
							}
							
						}
					}
				}
				if (counter < 2) {
					tempTP->setActive(false);
				}
			}
			objects[i]->update();
		}
	}
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getToDestroy()) {
			if (objects[i]->getControlled()) {
				//HERE1
				
				controlledDead = true;
			}
			if (objects[i]->getPickedUp()) {
				tempOb = getObjectById(objects[i]->getPickedUpById());
				tempP = std::dynamic_pointer_cast<Pickuper>(tempOb);
				tempP->drop();
			}
			changeObjectCount(objects[i]->getType(), -1);
			objects.erase(objects.begin() + i);
			i--;
			continue;
		}
	}
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
			pConsole->addCommand(commandDoAEODamage, projectiles[i]->getPosition().x, projectiles[i]->getPosition().y, 50, 10, projectiles[i]->getFaction());
			pConsole->addCommand(commandAddObject, objectSmoke, projectiles[i]->getPosition().x, projectiles[i]->getPosition().y, 0.0, 1.0);
			pConsole->addCommand(commandAddObject, objectSpark, projectiles[i]->getPosition().x, projectiles[i]->getPosition().y, 0.0, 1.0);
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
			doAEOHealing(end.x, end.y, 30, 2, beamsFaction[i]);
			doAEODamage(end.x, end.y, 30, 2, beamsFaction[i]);
		}
		if (((double)rand() / (RAND_MAX)) < 0.25) {
			pConsole->addCommand(commandAddObject, objectSpark, end.x, end.y, 0.0, 2.0);
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
	objects.push_back(std::make_shared<MainCharacter>(pInputManager, pSpriteCollection, pConsole, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addFootPrint(float x, float y) {
	objects.push_back(std::make_shared < FootPrint>(pSpriteCollection, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addSmoke(float x, float y, float height, float scale){
	objects.push_back(std::make_shared < Smoke>(pSpriteCollection, x, y, height, scale));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addExplosion(float x, float y, float size) {
	objects.push_back(std::make_shared<Explosion>(pSpriteCollection, pConsole, pSoundPlayer, x, y, size));
	setLatestId();
	setLatestConsole();
}


void ObjectCollection::addRoverTracks(float x, float y, float rotation){
	objects.push_back(std::make_shared<RoverTracks>(pSpriteCollection, x, y, rotation));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addRoverTracksMini(float x, float y, float rotation){
	objects.push_back(std::make_shared<RoverTracksMini>(pSpriteCollection, x, y, rotation));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addAction1Animation(float x, float y) {
	objects.push_back(std::make_shared<Action1Animation>(pSpriteCollection, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addWall(int x, int y, int w, int h) {
	objects.push_back(std::make_shared<Wall>(pSpriteCollection, x, y, w, h));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addEnemy(int x, int y) {
	objects.push_back(std::make_shared<Enemy>(pSpriteCollection, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addRover(int x, int y){
	objects.push_back(std::make_shared<Rover>(pInputManager, pSpriteCollection, pSoundPlayer, pConsole, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addCrate(int x, int y){
	objects.push_back(std::make_shared<Crate>(pSpriteCollection, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addRelay(int x, int y){
	objects.push_back(std::make_shared<Relay>(pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addScapMetalPile(int x, int y){
	objects.push_back(std::make_shared<ScrapMetalPile>(pSpriteCollection, x, y));
	objects[objects.size() - 1]->setRotation((rand() % 360));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addScapMetalDrop(int x, int y) {
	objects.push_back(std::make_shared<ScrapMetalDrop>(pSpriteCollection, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addMarketRelay(int x, int y){
	objects.push_back(std::make_shared<MarketRelay>(pSpriteCollection, pInputManager, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addAutoTurret(int x, int y){
	objects.push_back(std::make_shared<AutoTurret>(pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addJammer(int x, int y){
	objects.push_back(std::make_shared<Jammer>(pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addDefenseOrb(int x, int y){
	objects.push_back(std::make_shared<DefenseOrb>(pInputManager, pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addBuildDrone(int x, int y){
	objects.push_back(std::make_shared<BuildDrone>(pSpriteCollection, pSoundPlayer, x, y));
	setLatestId();
setLatestConsole();
}

void ObjectCollection::addSpark(int x, int y, int height, float colour) {
	objects.push_back(std::make_shared<Spark>(pSpriteCollection, glm::vec3(x, y, height), glm::vec3(((double)rand() / (RAND_MAX)) * 3 - 1.5, ((double)rand() / (RAND_MAX)) * 1.5, ((double)rand() / (RAND_MAX)) * 2), ((double)rand() / (RAND_MAX)) * 3.5 + 0.5, colour));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addGenerator(int x, int y) {
	objects.push_back(std::make_shared<Generator>(pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addEnemyBombRover(int x, int y) {
	objects.push_back(std::make_shared<EnemyBombRover>(pSpriteCollection, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addEnemyTurretRover(int x, int y){
	objects.push_back(std::make_shared<EnemyTurretRover>(pSpriteCollection, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addTeleporterPillar(int x, int y) {
	objects.push_back(std::make_shared<TeleporterPillar>(pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addBattery(int x, int y) {
	objects.push_back(std::make_shared<Battery>(pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addTeleporter(int x, int y){
	objects.push_back(std::make_shared<Teleporter>(pSpriteCollection, pConsole, pSoundPlayer, x, y));
	setLatestId();
	setLatestConsole();
}

void ObjectCollection::addProjectile(float _x, float _y, float _rotation, float _speed, int _fromID, int faction) {
	projectiles.push_back(std::make_shared<Projectile>(pSpriteCollection, pConsole, _x, _y, _rotation, _speed, _fromID, faction));
}

void ObjectCollection::addBeam(float _x1, float _y1, float _x2, float _y2, int _fromID, int _faction) {
	if (numBeams >= maxBeams) {
		std::cout << "MAX BEAMS REACHED\n";
	}
	beams[numBeams] = glm::vec4(_x1, _y1, _x2, _y2);
	beamsFrom[numBeams] = _fromID;
	beamsFaction[numBeams] = _faction;
	numBeams++;
}

void ObjectCollection::setLatestId() {
	objects[objects.size() - 1]->setId(nextId);
	nextId++; //when is this gonna overflow
}

void ObjectCollection::setLatestConsole() {
	objects[objects.size() - 1]->setConsolePointer(pConsole);
}

void ObjectCollection::runCollisionDetection(Object& o1, Object& o2) {
	if (o1.getPickedUp() || o2.getPickedUp()) return;
	if (o1.getCollidability() == movable) {
		if (!o2.getPickedUp() && o2.getCollidability() == movable) {
			if (o2.getCollidability() > o1.getCollidability()) {
				CollisionDetection::correctPosition(o2.getBoundingBoxPointer(), o1.getBoundingBoxPointer());
			}
			else {
				CollisionDetection::correctPositionBoth(o2.getBoundingBoxPointer(), o1.getBoundingBoxPointer());
			}
		}

	}
	if (o1.getCollidability() == controllable) {
		if (o1.getId() == cameraFocusId && o2.getType() == objectScrapMetalDrop && CollisionDetection::CheckRectangleIntersect(o1.getBoundingBoxPointer(), o2.getBoundingBoxPointer())) {
			pInventory->addResources(Resource::scrap, 1);
			o2.setToDestroy(true);
		}
		if (o2.getCollidability() == controllable) {
			CollisionDetection::correctPositionBoth(o2.getBoundingBoxPointer(), o1.getBoundingBoxPointer());
		}
	}
	if (o1.getCollidability() < movable) {
		if (!o2.getPickedUp() && o2.getCollidability() < 3 && o2.getCollidability() > o1.getCollidability()) {
			CollisionDetection::correctPosition(o2.getBoundingBoxPointer(), o1.getBoundingBoxPointer());
		}
	}
	if (o1.getCollidability() == droneCol && o2.getCollidability() == droneCol) {
		if (CollisionDetection::CheckRectangleIntersect(o2.getBoundingBoxPointer(), o1.getBoundingBoxPointer())) {
			CollisionDetection::correctPositionBoth(o2.getBoundingBoxPointer(), o1.getBoundingBoxPointer());
		}
	}
	if (o1.getType() == objectTeleporter && o2.getControlled() && CollisionDetection::CheckRectangleIntersect(o1.getBoundingBoxPointer(), o2.getBoundingBoxPointer())) {
		pConsole->addCommand(commandGoToEndScreen);
	}
}

void ObjectCollection::drawHealthBars() {
	std::shared_ptr<Living>living;
	for (int i = 0; i < objects.size(); i++) {
		//check if object inherits livings
		if (objects[i]->getLiving()) {
			living = std::dynamic_pointer_cast<Living>(objects[i]);
			pSpriteCollection->addRectDraw(objects[i]->getCenter().x - 30, objects[i]->getBoundingBox().y - 30, 60 * (living->getHealth() / living->getMaxHealth()), 5, 1000000, sf::Color(0, 255, 0, 10));
		}
	}
}

void ObjectCollection::doAEODamage(float x, float y, float range, float damage, int faction) {
	std::shared_ptr<Living> living;
	for (int i = 0; i < objects.size(); i++) {
		//check if object inherits living
		if (objects[i]->getFaction() != faction && objects[i]->getLiving() && !objects[i]->getPickedUp()) {
			if (pow((objects[i]->getBoundingBox().x + (objects[i]->getBoundingBox().w / 2)) - x, 2) + pow((objects[i]->getBoundingBox().y + (objects[i]->getBoundingBox().h / 2)) - y, 2) < pow(range, 2)) {
				//do damage
				living = std::dynamic_pointer_cast<Living>(objects[i]);
				living->doDamage(damage);
				if (living->getHealth() <= 0) {
					objects[i]->setToDestroy(true);
				}
			}
		}
	}
}

void ObjectCollection::doAEOHealing(float x, float y, float range, float amount, int faction){
	std::shared_ptr<Living> living;
	for (int i = 0; i < objects.size(); i++) {
		//check if object inherits living
		if (objects[i]->getFaction() == faction && objects[i]->getLiving() && !objects[i]->getPickedUp()) {
			if (pow((objects[i]->getBoundingBox().x + (objects[i]->getBoundingBox().w / 2)) - x, 2) + pow((objects[i]->getBoundingBox().y + (objects[i]->getBoundingBox().h / 2)) - y, 2) < pow(range, 2)) {
				//do healing
				living = std::dynamic_pointer_cast<Living>(objects[i]);
				living->doDamage(-amount);
			}
		}
	}
}

void ObjectCollection::setDebug(bool _debug) {
	debug = _debug;
}

std::shared_ptr<Object> ObjectCollection::getTarget(glm::vec2 position, int faction, float range) {
	int targetFaction = 0;
	if (faction == 0) {
		targetFaction = 1;
	}

	int minDistance = 10000;
	int minIndex = -1;
	int objectsSize = objects.size(); // Store size if not changing in the loop
	
	for (int j = 0; j < objectsSize; j++) {

		if (objects[j]->getLiving()) {
			if ((targetFaction == objects[j]->getFaction())) {

				int distance = CollisionDetection::getDistance(position, objects[j]->getCenter());

				if (distance < minDistance) {
					minDistance = distance;
					minIndex = j;
				}
			}
		}
	}
	if (minIndex == -1 || minDistance > range) {
		return std::shared_ptr<Object>();
	}
	return objects[minIndex];
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
	std::shared_ptr<Object> object = getObjectById(id);
	if (object == nullptr) {
		return;
	}
	std::shared_ptr<Pickuper> pickuper;
	if (!(pickuper = std::dynamic_pointer_cast<Pickuper>(object))) {
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
	std::shared_ptr<Object> object1 = getObjectById(id);
	if (object1 == nullptr) {
		return;
	}
	std::shared_ptr<Pickuper> pickuper;
	if (!(pickuper = std::dynamic_pointer_cast<Pickuper>(object1))) {
		std::cout << "OBJECT WITH ID " << id << " NOT A PICKUPER\n";
		return;
	}
	if (!pickuper->getHolding()) {
		std::cout << "OBJECT WITH ID " << id << " NOT HOLDING ANYTHING\n";
		return;
	}
	
	std::shared_ptr<Object> object2 = getObjectById(pickuper->getIdHeld());
	if (object2 == nullptr) {
		return;
	}
	BoundingBox* temp = object2->getBoundingBoxPointer(); 
	if (!checkArea(glm::vec4(temp->x, temp->y, temp->w, temp->h), object1->getId(), object2->getId())) return;
	pickuper->drop();

	object2->setPickedUp(false);
	object2->setCenter(pickuper->getPickupPos());
	object2->setRotation(pickuper->getDropRotation());
	pickuper->drop();
}

void ObjectCollection::runDropWithoutPickuper(int id) {
	std::shared_ptr<Object> object = getObjectById(id);
	object->setPickedUp(false);
}

glm::vec2 ObjectCollection::getClosestControllablePosition(int currentID) {
	int mouseX = pInputManager->translatedMouseX;
	int mouseY = pInputManager->translatedMouseY;
	std::shared_ptr<Object> current = getObjectById(currentID);
	glm::vec2 closestPos = glm::vec2(-1000);
	if (current == nullptr) {
		std::cout << "current object does not exist\n";
		return closestPos;
	}
	int currentX = current->getBoundingBox().x;
	int currentY = current->getBoundingBox().y;
	std::shared_ptr<Controllable> controllable;
	if (!(controllable = std::dynamic_pointer_cast<Controllable>(current))) {
		std::cout << "current object given is not controllable\n";
	}
	int range = controllable->getRange();
	int closestDistance = 100000;
	int distanceFromCurrent = 0;
	int distanceFromMouse = 0;
	
	for (int i = 0; i < objects.size(); i++) {
		if ((controllable = std::dynamic_pointer_cast<Controllable>(objects[i]))) {
			//if another object is found that is controllable and not the current object
			//get distance, see if its within range
			distanceFromCurrent = CollisionDetection::getDistance(glm::vec2(currentX, currentY), glm::vec2(objects[i]->getBoundingBox().x, objects[i]->getBoundingBox().y));
			distanceFromMouse = CollisionDetection::getDistance(glm::vec2(mouseX, mouseY), glm::vec2(objects[i]->getBoundingBox().x, objects[i]->getBoundingBox().y));
			if (distanceFromCurrent < range && distanceFromMouse < closestDistance) {
				//if closest so far, record distance and the id of that object
				closestDistance = distanceFromMouse;
				closestPos = objects[i]->getCenter();
			}
		}
	}
	return closestPos;
}

int ObjectCollection::getClosestControllable(int currentID){
	int mouseX = pInputManager->translatedMouseX;
	int mouseY = pInputManager->translatedMouseY;
	std::shared_ptr<Object> current = getObjectById(currentID);
	if (current == nullptr) {
		std::cout << "current object does not exist\n";
		return -1;
	}
	int currentX = current->getBoundingBox().x;
	int currentY = current->getBoundingBox().y;
	std::shared_ptr<Controllable> controllable;
	if (!(controllable = std::dynamic_pointer_cast<Controllable>(current))) {
		std::cout << "current object given is not controllable\n";
	}
	int range = controllable->getRange();
	int closestDistance = 100000;
	int distanceFromCurrent = 0;
	int distanceFromMouse = 0;
	int closestID = -1;
	for (int i = 0; i < objects.size(); i++) {
		if ((controllable = std::dynamic_pointer_cast<Controllable>(objects[i]))) {
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

std::shared_ptr<Object> ObjectCollection::getClosestPowerNode()
{
	int mouseX = pInputManager->translatedMouseX;
	int mouseY = pInputManager->translatedMouseY;
	int closestDistance = 100000;
	int distanceFromMouse = 0;
	std::shared_ptr<Object> ptr = std::shared_ptr<Object>();
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getIsPowerNode()) {
			distanceFromMouse = CollisionDetection::getDistance(glm::vec2(mouseX, mouseY), glm::vec2(objects[i]->getBoundingBox().x, objects[i]->getBoundingBox().y));
			if (distanceFromMouse < closestDistance) {
				//if closest so far, record distance and the id of that object
				closestDistance = distanceFromMouse;
				ptr = objects[i];;
			}
		}
	}
	return ptr;
}

std::shared_ptr<Object> ObjectCollection::getClosestPowerNode(int currentID)
{
	std::shared_ptr<Object> ptr = std::shared_ptr<Object>();
	int mouseX = pInputManager->translatedMouseX;
	int mouseY = pInputManager->translatedMouseY;
	std::shared_ptr<Object> current = getObjectById(currentID);
	if (current == nullptr) {
		std::cout << "current object does not exist\n";
		return ptr;
	}
	int currentX = current->getBoundingBox().x;
	int currentY = current->getBoundingBox().y;
	std::shared_ptr<Controllable> controllable;
	if (!(controllable = std::dynamic_pointer_cast<Controllable>(current))) {
		std::cout << "current object given is not controllable\n";
	}
	int range = controllable->getRange();
	int closestDistance = 100000;
	int distanceFromCurrent = 0;
	int distanceFromMouse = 0;
	for (int i = 0; i < objects.size(); i++) {
		if ((controllable = std::dynamic_pointer_cast<Controllable>(objects[i]))) {
			//if another object is found that is controllable and not the current object
			//get distance, see if its within range
			distanceFromCurrent = CollisionDetection::getDistance(glm::vec2(currentX, currentY), glm::vec2(objects[i]->getBoundingBox().x, objects[i]->getBoundingBox().y));
			distanceFromMouse = CollisionDetection::getDistance(glm::vec2(mouseX, mouseY), glm::vec2(objects[i]->getBoundingBox().x, objects[i]->getBoundingBox().y));
			if (distanceFromCurrent < range && distanceFromMouse < closestDistance) {
				//if closest so far, record distance and the id of that object
				closestDistance = distanceFromMouse;
				ptr = objects[i];
			}
		}
	}
	return ptr;
}

void ObjectCollection::pullToPoint(float x, float y, int range){
	glm::vec2 direction;
	float distance;
	for (int i = 0; i < objects.size(); i++) {
		if (std::dynamic_pointer_cast<ScrapMetalDrop>(objects[i])) {
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

std::shared_ptr<Object> ObjectCollection::getObjectById(int id)
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
	objects.clear();
	projectiles.clear();
	nextId = 0;
	teleporterExists = false;
	for (auto& pair : objectCounter) {
		pair.second = 0;
	}
}

void ObjectCollection::AddToInventory(Resource resource, int amount){
	pInventory->addResources(resource, amount);
}

void ObjectCollection::setLastToBuild(){
	objects[objects.size() - 1]->setToBuild(true);
}

int ObjectCollection::getGeneratorCount() {
	return objectCounter[objectGenerator];
}

void ObjectCollection::setLastRotation(float _rotation){
	objects[objects.size() - 1]->setRotation(_rotation);
}

bool ObjectCollection::checkArea(glm::vec4 _box){
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getCollidability() != none && objects[i]->getCollidability() != droneCol && CollisionDetection::CheckRectangleIntersect(objects[i]->getBoundingBoxPointer(), &_box)) {
			return false;
		}
	}
	return true;
}

bool ObjectCollection::checkArea(glm::vec4 _box, int exclusionID1, int exclusionID2) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getCollidability() != none && objects[i]->getCollidability() != droneCol && objects[i]->getId() != exclusionID1 && objects[i]->getId() != exclusionID2 && CollisionDetection::CheckRectangleIntersect(objects[i]->getBoundingBoxPointer(), &_box)) {
			return false;
		}
	}
	return true;
}

void ObjectCollection::changeObjectCount(ObjectType type, int change){
	objectCounter[type] += change;
}

glm::vec2 ObjectCollection::getGeneratorPos(){
	return generatorPos;
}

void ObjectCollection::controlClosest(){

}
