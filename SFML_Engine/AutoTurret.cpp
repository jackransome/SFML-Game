#include "AutoTurret.h"

AutoTurret::AutoTurret(SpriteCollection* _pSpriteCollection, Console* _pConsole, float _x, float _y, b2World* _pPhysicsWorld) :
	Object(_x, _y, 24, 24, 0, immovable, true, _pPhysicsWorld),
	Living(100, 1, factionFriendly)
{
	target = glm::vec2(0, 0);
	pSpriteCollection = _pSpriteCollection;
	pConsole = _pConsole;
	type = objectNull;
	baseStack = SpriteStack(pSpriteCollection, "autoturret_base_stack", 12, 12, 4, 2); //CHANGE
	barrelStack = SpriteStack(pSpriteCollection, "autoturret_barrel_stack", 16, 16, 8, 2); //CHANGE
	targetingRange = 600;
	canBePickedUp = true;
	maxReload = 15;
	type = objectAutoTurret;

	// Create a kinematic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set((float)_x / 100, (float)_y / 100);
	physicsBody = pPhysicsWorld->CreateBody(&bodyDef);

	// Attach a shape to the kinematic body
	b2PolygonShape kinematicBox;
	kinematicBox.SetAsBox((boundingBox.w / 2)/100, (boundingBox.h/2)/100);
	physicsBody->CreateFixture(&kinematicBox, 0.0f);

	physicsBodyType = 1;
}

void AutoTurret::update() {
	//get angle from our center to the target and set barrelRotation

	//std::cout << target.x << "|" << target.y << "|" << barrelRotation << "\n";
	//if ready to fire, fire (via command)
	if (hasTarget ){
		glm::vec2 center = getCenter();
		barrelRotation = 180.0f * atan2((target.y - center.y), (target.x - center.x)) / (3.1415);
		if (reloadTimer <= 0) {
			glm::vec2 distVector = pConsole->getControlPosition() - getCenter();
			float distance = sqrt(distVector.x * distVector.x + distVector.y * distVector.y);
			float targetVelMagnitude = sqrt(targetVel.x * targetVel.x + targetVel.y * targetVel.y);
			float timetoTarget = distance / projectileSpeed;
			target += targetVel * timetoTarget;

			pConsole->addCommand(commandPlaySound, "laser_shot", 0.2 / (1 + distance / 100));

			glm::vec2 shootPos = getCenter() + glm::vec2(18 * cos(3.1415 * barrelRotation / 180.0f), 18 * sin(3.1415 * barrelRotation / 180.0f) - 16);
			float radians = atan2((target.y - shootPos.y), (target.x - shootPos.x));

			pConsole->addCommand(commandAddProjectile, shootPos.x, shootPos.y, radians, projectileSpeed, id);
			reloadTimer = maxReload;




			/*
			
			
			targetPos += targetVel every frame

			projpos += projVel every frame
			

			projePos + x*projVel = targetPos + x*tergetVel
			(projVel - targetVel) = (targetPos - projPos)/x
			projVel = (targetPos - projPos)/x + targetVel


			
			*/
		}
	}
	physicsBody->SetTransform(b2Vec2(boundingBox.x/100, boundingBox.y/100), 0);
	reloadTimer--;
}

void AutoTurret::draw() {
	float radians = 3.1415 * (barrelRotation-180) / 180.0f;
	glm::vec2 lightPos = getCenter() + glm::vec2(1 * cos(radians) -1 * sin(radians), 1 * sin(radians) + 1 * cos(radians) - 26);
	baseStack.draw(boundingBox.x, boundingBox.y, boundingBox.y, rotation);
	barrelStack.draw(boundingBox.x-4, boundingBox.y-14, boundingBox.y+1, barrelRotation-90);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(160, 214, 255), 2, 1, false);
	pSpriteCollection->drawLightSource(lightPos, glm::vec3(160, 214, 255), 0.2, 0, false);
}

void AutoTurret::setTarget(int x, int y, float xvel, float yvel) {
	target.x = x;
	target.y = y;
	targetVel.x = xvel;
	targetVel.y = yvel;
	hasTarget = true;
}

void AutoTurret::RemoveTarget() {
	hasTarget = false;
}

int AutoTurret::getTargetingRange(){
	return targetingRange;
}
