#include "Textbox.h"

Textbox::Textbox(Console* _pConsole, SpriteCollection* _pSpriteCollection, TextboxType _type, glm::vec4 _bbox, std::string _text) {
	pConsole = _pConsole;
	pSpriteCollection = _pSpriteCollection;
	type = _type;
	bbox = _bbox;
	text = _text;
}

glm::vec4 Textbox::getBbox()
{
	return bbox;
}

DisplayTextbox::DisplayTextbox(Console* _pConsole, SpriteCollection* _pSpriteCollection, glm::vec4 _bbox, std::string _text) :
Textbox(_pConsole, _pSpriteCollection, TextboxType::display, _bbox, _text) {

}

void DisplayTextbox::draw() {
	pSpriteCollection->addTextDraw(2, bbox[0], bbox[1], 1000005, text, 14, sf::Color(255, 255, 255, 255));
}