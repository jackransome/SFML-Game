#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "Living.h"
#include "SpriteStack.h"

class AutoTurret : public Object, public Living {
public:
	AutoTurret(SpriteCollection* _pSpriteCollection, Console* _pConsole, float _x, float _y, b2World* _pPhysicsWorld);
	virtual void update() override;
	virtual void draw() override;
	void setTarget(int x, int y, float xvel, float yvel);
	void RemoveTarget();
	int getTargetingRange();
private:
	SpriteCollection* pSpriteCollection;
	Console* pConsole;
	float projectileSpeed = 30;
	glm::vec2 target;
	glm::vec2 targetVel;
	float barrelRotation = 0;
	SpriteStack baseStack;
	SpriteStack barrelStack;
	bool hasTarget = false;
	int targetingRange;
	int reloadTimer = 0;
	int maxReload;
};