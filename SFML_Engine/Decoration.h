#pragma once
#include "Object.h"
#include "SpriteSheet.h"
#include "InputManager.h"

class Decoration : public Object {
public:
	Decoration(SpriteCollection* _pSpriteCollection, float x, float y);
protected:
	SpriteCollection* pSpriteCollection;
	Graphics* pGraphics;
};