#pragma once
#include "Decoration.h"

class Smoke : public Decoration {
public:
	Smoke(SpriteCollection* _pSpriteCollection, float x, float y);
	virtual void draw() override;
	virtual void update() override;
protected:
	float decay;
	float opacity;
	float height;
	float riseSpeed;
	std::string image;
};