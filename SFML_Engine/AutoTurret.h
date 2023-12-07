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
	void setTarget(std::shared_ptr<Object> _target);
	virtual void onDeath() override;
	void RemoveTarget();
	int getTargetingRange();
private:
	SpriteCollection* pSpriteCollection;
	Console* pConsole;
	float barrelRotation = 0;
	SpriteStack baseStack;
	SpriteStack barrelStack;
	SoundPlayer* pSoundPlayer;
	std::weak_ptr<Object> target;
	glm::vec2 shootPos;
	int reloadTimer = 0;
	int maxReload;
	float projectileSpeed = 60;
};