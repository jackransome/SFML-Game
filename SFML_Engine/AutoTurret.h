#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "Living.h"
#include "SpriteStack.h"
#include "SoundPlayer.h"

class AutoTurret : public Object, public Living {
public:
	AutoTurret(SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, float _x, float _y);
	virtual void update() override;
	virtual void draw() override;
	virtual void drawBuilding() override;
	void setTarget(int x, int y, float xvel, float yvel);
	virtual void onDeath() override;
	void RemoveTarget();
	int getTargetingRange();
private:
	SpriteCollection* pSpriteCollection;
	Console* pConsole;
	glm::vec2 target;
	glm::vec2 targetVel;
	float barrelRotation = 0;
	SpriteStack baseStack;
	SpriteStack barrelStack;
	SoundPlayer* pSoundPlayer;
	bool hasTarget = false;
	int targetingRange;
	glm::vec2 shootPos;
	int reloadTimer = 0;
	int maxReload;
	float projectileSpeed = 60;
};