#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "Living.h"
#include "SoundPlayer.h"


class Enemy : public Object, public Living {
public:
	Enemy(SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, float x, float y, b2World* _pPhysicsWorld);
	virtual void update() override;
	virtual void draw() override;
	virtual void onDeath() override;
	void setTarget(int x, int y);
	int getTargetingRange();
	void RemoveTarget();
private:
	SpriteCollection* pSpriteCollection;
	float maxVel;
	float acceleration;
	bool hasTarget = false;
	int targetingRange;
	glm::vec2 target;
	glm::vec2 velocity;
	glm::vec2 position;
	int damageRange;
	int reloadTimer = 0;
	int maxReload;
	void normaliseVec(glm::vec2 *vec);
	SoundPlayer* pSoundPlayer;
	int AmbientSoundId;
	SpriteSheet mainAnimation;
};