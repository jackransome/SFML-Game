#include "Item.h"

Item::Item(bool _canStack, bool _isTool, ItemType _type, SpriteCollection* _pSpriteCollection, std::string _textureName) {
	canStack = _canStack;
	isTool = _isTool;
	type = _type;
	pSpriteCollection = _pSpriteCollection;
	texture = pSpriteCollection->getPointerFromName(_textureName);
}

Item::~Item() { }

void Item::draw(float _x, float _y, float _z, float _scale) {
	pSpriteCollection->addImageDraw(texture, _x, _y, _z, _scale, 32, 32);
}

bool Item::getIsTool() {
	return isTool;
}

bool Item::getCanStack() {
	return canStack;
}

ItemType Item::getType() {
	return type;
}
