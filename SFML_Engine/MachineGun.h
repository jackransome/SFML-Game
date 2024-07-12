#pragma once
#include "Tool.h"
#include "SoundPlayer.h"

class MachineGun : public Tool {
public:
	MachineGun(Console* _pConsole, SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer);
	~MachineGun();
	void activate(glm::vec2 position, glm::vec2 target, int _parentId) override;
	void drawUsing(glm::vec2 position, glm::vec2 target, int z) override;
	void update() override;
private:
	float angleFromPositionToPosition(const glm::vec2& vec1, const glm::vec2& vec2);
	TextureWrapper* usedTexture;
	TextureWrapper* usedFlippedTexture;
	float charge = 0;
	bool activated = false;
	bool beamSoundPlaying = false;
	int beamSoundId = -1;
	SoundPlayer* pSoundPlayer;
	bool latch = false;
	bool lastLatch = false;
};