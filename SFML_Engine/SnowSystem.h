#pragma once
#include "SpriteCollection.h"
#include "SoundPlayer.h"

struct SnowPart {
	float x;
	float y;
	float phase;
	float sx;
	float sy;
	float sw;
	float sh;
	float opacity;
	float maxOpacity;
	float rotation;
};

class SnowSystem {
public:
	SnowSystem() {}
	SnowSystem(SpriteCollection* _pSpriteCollection, SoundPlayer* _pSoundPlayer, Camera* _pCamera, int* _pScreenW, int* _pScreenH, glm::vec2 cameraPos);
	void run();
	void draw(float z);
	void drawMenu(float z, float scale);
	void setFallAngle(float _fallAngle);
	void changeFallAngle(float _fallAngle);
	void setSpeed(float _fallSpeed);
	void changeSpeed(float _fallSpeed);
	void setOpacity(float _opacity);
	void changeOpacity(float _opacity);
	void setSize(int _size);
	void changeSize(int _size);
	void setSinMultiplier(float sM);
	void setActive(bool _active);
private:
	bool active = false;
	SpriteCollection* pSpriteCollection;
	SnowPart getNewSnowPart(glm::vec2 cameraPos);
	SnowPart snowParts[150];
	float fallAngle = 1.6;
	float fallAngleTarget = 0;
	float fallSpeed = 1;
	float fallSpeedTarget = 0;
	float size = 50;
	float sizeTarget = 0;
	float opacity = 0;
	float opacityTarget = 0;
	float sinMultiplier = 1;


	int* pScreenW;
	int* pScreenH;
	
	int maxSize = 150;
	int borderSize = 800;
	int time;

	TextureWrapper* pTexture;
	TextureWrapper* pMenuTexture;
	Camera* pCamera;
	SoundPlayer* pSoundPlayer;
	int windSoundID;
	bool menuMode = false;
};