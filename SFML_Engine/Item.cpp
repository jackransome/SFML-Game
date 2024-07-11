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
	pSpriteCollection->addImageDraw(texture, _x - ((iconSize * _scale)/2), _y - ((iconSize * _scale) / 2), _z, _scale, iconSize * _scale, iconSize * _scale);
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
