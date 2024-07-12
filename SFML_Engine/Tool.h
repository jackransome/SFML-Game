#pragma once
#include "Item.h"
#include "Inventory.h"
#include <glm/glm.hpp>
#include "Console.h"
#include "SpriteCollection.h"

class Tool : public Item {
public:
	Tool(int _maxAttachments, ItemType _type, Console* _pConsole, SpriteCollection* _pSpriteCollection, std::string _textureName);
	~Tool();
	virtual void activate(glm::vec2 position, glm::vec2 target, int _parentId) = 0;
	virtual void drawUsing(glm::vec2 position, glm::vec2 target, int z) = 0;
	virtual void update() = 0;
	Inventory* getAttachments();
protected:
	Inventory attachments;
	Console* pConsole;
};