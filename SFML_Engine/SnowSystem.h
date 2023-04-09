#pragma once
#include "SpriteCollection.h"

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
	SnowSystem(SpriteCollection* _pSpriteCollection, int* _pScreenW, int* _pScreenH, glm::vec2 cameraPos);
	void run(glm::vec2 cameraPos);
	void draw(float z);
	void setFallAngle(float _fallAngle);
	void setSpeed(float _fallSpeed);
	void setOpacity(float _opacity);
	void setSize(int _size);
private:
	SpriteCollection* pSpriteCollection;
	SnowPart getNewSnowPart(glm::vec2 cameraPos);
	SnowPart getNewSnowPartInit(glm::vec2 cameraPos);
	SnowPart snowParts[150];
	float fallAngle = 1.6;
	float fallSpeed = 1;
	int* pScreenW;
	int* pScreenH;
	int size = 50;
	int maxSize = 150;
	int borderSize = 800;
	int time;
	float opacity = 0;
	TextureWrapper* pTexture;
};