#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "Living.h"
#include "SoundPlayer.h"


class Enemy : public Object, public Living {
public:
	Enemy(SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, float x, float y);
	~Enemy() override;
	virtual void update() override;
	virtual void draw() override;
	virtual void onDeath() override;
	void setTarget(std::shared_ptr<Object> _target);
	int getTargetingRange();
	void RemoveTarget();
private:
	SpriteCollection* pSpriteCollection;
	float maxVel;
	float acceleration;
	std::weak_ptr<Object> target;
	int damageRange;
	int reloadTimer = 0;
	int maxReload;
	void normaliseVec(glm::vec2 *vec);
	SoundPlayer* pSoundPlayer;
	int AmbientSoundId;
	SpriteSheet mainAnimation;
};