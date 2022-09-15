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
};

class SnowSystem {
public:
	SnowSystem() {}
	SnowSystem(SpriteCollection* _pSpriteCollection, int _screenW, int _screenH, glm::vec2 cameraPos);
	void run(glm::vec2 cameraPos);
	void draw();
	void setFallAngle(float _fallAngle);
	void setSpeed(float _fallSpeed);
private:
	SpriteCollection* pSpriteCollection;
	SnowPart getNewSnowPart(glm::vec2 cameraPos);
	SnowPart snowParts[40];
	float fallAngle = 1.6;
	float fallSpeed = 1;
	int screenW;
	int screenH;
	int size = 40;
	int borderSize = 800;
	int time;
};