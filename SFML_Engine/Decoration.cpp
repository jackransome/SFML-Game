#include "Decoration.h"

Decoration::Decoration(SpriteCollection* _pSpriteCollection, float x, float y) :
	Object(x, y, 0, 0, 0, false, false) {
	pSpriteCollection = _pSpriteCollection;
}