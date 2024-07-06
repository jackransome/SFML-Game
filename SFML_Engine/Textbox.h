#pragma once
#include "SpriteCollection.h"
#include "Console.h"
#include "SpriteSheet.h"

enum class TextboxType {
	display, input
};

class Textbox {
public:
	Textbox(Console* _pConsole, SpriteCollection* _pSpriteCollection, TextboxType _type, glm::vec4 _bbox, std::string _text);
	virtual void draw() {};
	glm::vec4 getBbox();

protected:
	Console* pConsole;
	glm::vec4 bbox;
	TextboxType type;
	SpriteCollection* pSpriteCollection;
	std::string text;
};

class DisplayTextbox : public Textbox {
public:
	DisplayTextbox(Console* _pConsole, SpriteCollection* _pSpriteCollection, glm::vec4 _bbox, std::string _text);
	virtual void draw() override;
};