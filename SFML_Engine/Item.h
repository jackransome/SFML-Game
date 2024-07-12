#pragma once
#include "SpriteSheet.h"

enum class ItemType {
	scrap, buildTool, count
};

class Item {
public:
	Item(bool _canStack, bool _isTool, ItemType _type, SpriteCollection* _pSpriteCollection, std::string textureName);
	~Item();
	void draw(float _x, float _y, float _z, float _scale);
	bool getIsTool();
	bool getCanStack();
	ItemType getType();
protected:
	TextureWrapper* texture;
	SpriteCollection* pSpriteCollection;
private:
	bool canStack = false;
	bool isTool = false;
	ItemType type;
	int iconSize = 32;
};