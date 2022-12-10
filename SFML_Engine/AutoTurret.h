#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "Living.h"
#include "SpriteStack.h"

class AutoTurret : public Object, public Living {
public:
	AutoTurret(SpriteCollection* _pSpriteCollection, Console* _pConsole, float x, float y);
	virtual void update() override;
	virtual void draw() override;
	void setTarget(int x, int y);
	void RemoveTarget();
	int getTargetingRange();
private:
	SpriteCollection* pSpriteCollection;
	Console* pConsole;
	glm::vec2 target;
	float barrelRotation = 0;
	SpriteStack baseStack;
	SpriteStack barrelStack;
	bool hasTarget = false;
	int targetingRange;
};