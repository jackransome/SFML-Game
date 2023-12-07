#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "Living.h"
#include "SoundPlayer.h"


class EnemyBombRover : public Object, public Living {
public:
	EnemyBombRover(SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, float x, float y);
	~EnemyBombRover() override;
	virtual void update() override;
	virtual void draw() override;
	virtual void onDeath() override;
	void setTarget(std::shared_ptr<Object> _target);
	int getTargetingRange();
	void RemoveTarget();
private:
	void adjustDirection(const glm::vec2& center, const glm::vec2& target, float& direction, float amount);
	void moveTowardsTarget(float& direction, float amount);
	float normalizeAngle(float angle);
	bool isAngleWithinThreshold(const glm::vec2& point1, const glm::vec2& point2, float angle, float threshold);
	SpriteCollection* pSpriteCollection;
	float maxVel;
	float acceleration;
	int explodeRange;
	SoundPlayer* pSoundPlayer;
	int AmbientSoundId;
	SpriteStack stack;
	int blinkCounter = 0;
	float speed = 2.5;
	int moveSoundId;
	bool moveSoundPlaying = false;
	int trackTimer = 0;

	std::weak_ptr<Object> target;

};