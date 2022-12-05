#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "Living.h"
#include "Mineable.h"

class ScrapMetalPile : public Object, public Mineable {
public:
	ScrapMetalPile(SpriteCollection* _pSpriteCollection, int x, int y);
	virtual void draw() override;
private:
	SpriteStack spriteStack;
	SpriteCollection* pSpriteCollection;
};