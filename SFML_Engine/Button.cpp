#include "Button.h"

Button::Button(SpriteCollection* _pSpriteCollection, ButtonType _type, glm::vec4 _bbox){
	pSpriteCollection = _pSpriteCollection;
	type = _type;
	bbox = _bbox;
}

void Button::drawBox(){
	if (active) {
		pSpriteCollection->addAbsoluteRectDraw(bbox[0], bbox[1], bbox[2], bbox[3], 10000, sf::Color(200,200,200,255), 0.3);
	}
	else {
		pSpriteCollection->addAbsoluteRectDraw(bbox[0], bbox[1], bbox[2], bbox[3], 10000, sf::Color::White, 0.3);
	}
}

BuildButton::BuildButton(SpriteCollection* _pSpriteCollection, BuildType _buildType, glm::vec4 _bbox) :
	Button(_pSpriteCollection, ButtonType::build, _bbox) {
	buildType = _buildType;
}

void BuildButton::press(){

}

void BuildButton::draw()
{
	drawBox();
}
