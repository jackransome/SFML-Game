#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "Living.h"
#include "SoundPlayer.h"


class BuildDrone : public Object {
public:
	BuildDrone(SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, float x, float y);
	~BuildDrone() override;
	virtual void update() override;
	virtual void draw() override;
	virtual void drawBuilding() override;
	void setTarget(std::shared_ptr<Object> _target);
	void RemoveTarget();
	bool getHasTarget();
private:
	SpriteCollection* pSpriteCollection;
	int beamSoundId;
	bool beamSoundPlaying = false;
	float maxVel;
	float acceleration;
	float height = 0;
	std::weak_ptr<Object> target;
	float distance = 1000;
	float buildRange = 50;
	SoundPlayer* pSoundPlayer;
	SpriteStack mainStack;
	int bob_counter = 0;
	bool building = false;
};