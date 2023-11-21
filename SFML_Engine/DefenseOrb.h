#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "InputManager.h"
#include "Living.h"
#include "Controllable.h"
#include "SoundPlayer.h"

class DefenseOrb : public Object, public Living, public Controllable {
public:
	DefenseOrb(InputManager* _pInputManager, SpriteCollection* _pSpriteCollection, Console* _pConsole, SoundPlayer* _pSoundPlayer, float _x, float _y);
	~DefenseOrb();
	virtual void onDeath() override;
	virtual void update() override;
	virtual void draw() override;
private:
	SoundPlayer* pSoundPlayer;
	int beamSoundId;
	bool beamSoundPlaying = false;

	float beamCharge;
	float bob_counter;
	glm::vec2 target;
	SpriteStack mainStack;
	SpriteCollection* pSpriteCollection;
	InputManager* pInputManager;
	Console* _pConsole;
};