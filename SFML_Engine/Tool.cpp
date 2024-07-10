#include "Tool.h"
#include "iostream"
Tool::Tool(int _maxAttachments, ItemType _type, Console* _pConsole, SpriteCollection* _pSpriteCollection, std::string _textureName) :
Item(false, true, _type, _pSpriteCollection, _textureName) {
	attachments = Inventory(_maxAttachments, _maxAttachments, false);
	pConsole = _pConsole;
}

Tool::~Tool() {}

Inventory* Tool::getAttachments() {
	return &attachments;
}