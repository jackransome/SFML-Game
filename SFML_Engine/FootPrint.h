#pragma once
#pragma once
#include "Decoration.h"

class FootPrint : public Decoration {
public:
	FootPrint(SpriteCollection* _pSpriteCollection, float x, float y);
	virtual void draw() override;
	virtual void update() override;
protected:
	float decay;
	float opacity;
};