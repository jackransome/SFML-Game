#pragma once
#include "Object.h"
#include "SpriteStack.h"
#include "Living.h"

class ScrapMetalPile : public Object {
public:
	ScrapMetalPile(SpriteCollection* _pSpriteCollection, int x, int y);
	virtual void draw() override;
private:
	SpriteStack spriteStack;
	SpriteCollection* pSpriteCollection;
};