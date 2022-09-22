#pragma once
#include "Decoration.h"

class RoverTracks : public Decoration {
public:
	RoverTracks(SpriteCollection* _pSpriteCollection, float x, float y, float _rotation);
	virtual void draw() override;
	virtual void update() override;
protected:
	float rotation;
	float decay;
	float opacity;
	SpriteSheet spriteSheet;
};