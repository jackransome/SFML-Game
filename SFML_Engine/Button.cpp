#include "Button.h"

Button::Button(SpriteCollection* _pSpriteCollection, ButtonType _type, glm::vec4 _bbox){
	pSpriteCollection = _pSpriteCollection;
	type = _type;
	bbox = _bbox;
}

bool Button::getActive(){
	return active;
}

void Button::setHover(bool hover){
	hoverOver = hover;
}

bool Button::getHover(){
	return hoverOver;
}

glm::vec4 Button::getBbox(){
	return bbox;
}

void Button::drawBox(){
	pSpriteCollection->setFullBrightMode(true);
	if (!active) {
		pSpriteCollection->addRectDraw(bbox[0], bbox[1], bbox[2], bbox[3], 10000, sf::Color(0, 0, 0, 80));
	}
	else {
		if (hoverOver) {
			pSpriteCollection->addRectDraw(bbox[0], bbox[1], bbox[2], bbox[3], 10000, sf::Color(200, 200, 200, 80));
		}
		else {
			pSpriteCollection->addRectDraw(bbox[0], bbox[1], bbox[2], bbox[3], 10000, sf::Color(255, 255, 255, 80));
		}
	}
	pSpriteCollection->addRectDraw(bbox[0], bbox[1], 4, bbox[3], 10000, sf::Color(120, 120, 120, 80));
	pSpriteCollection->addRectDraw(bbox[0], bbox[1], bbox[2], 4, 10000, sf::Color(120, 120, 120, 80));
	pSpriteCollection->addRectDraw(bbox[0]+bbox[2]-4, bbox[1], 4, bbox[3], 10000, sf::Color(120, 120, 120, 80));
	pSpriteCollection->addRectDraw(bbox[0], bbox[1]+bbox[3] - 4, bbox[2], 4, 10000, sf::Color(120, 120, 120, 80));
	pSpriteCollection->setFullBrightMode(false);
}

BuildButton::BuildButton(SpriteCollection* _pSpriteCollection, Builder* _pBuilder, BuildType _buildType, glm::vec4 _bbox) :
	Button(_pSpriteCollection, ButtonType::build, _bbox) {
	buildType = _buildType;
	pBuilder = _pBuilder;
}

void BuildButton::press(){
	
	pBuilder->activate(buildType);
}

void BuildButton::draw(){
	drawBox();
	
}

void BuildButton::update(){
	if (pBuilder->checkResources(buildType)) {
		active = true;
	} else {
		active = false;
	}
}
