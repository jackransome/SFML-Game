#include "Button.h"

Button::Button(Console* _pConsole, SpriteCollection* _pSpriteCollection, ButtonType _type, glm::vec4 _bbox){
	pSpriteCollection = _pSpriteCollection;
	type = _type;
	bbox = _bbox;
	pConsole = _pConsole;
	imgReady = SpriteSheet(pSpriteCollection, "button_ready", 250, 50, 1, 1);
	imgHover = SpriteSheet(pSpriteCollection, "button_hover", 250, 50, 1, 1);
	imgGrey = SpriteSheet(pSpriteCollection, "button_greyed_out", 250, 50, 1, 1);
	imgReady.setOpacity(0.5);
	imgHover.setOpacity(0.5);
	imgGrey.setOpacity(0.5);

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
	if (!active) {
		//pSpriteCollection->addRectDraw(bbox[0], bbox[1], bbox[2], bbox[3], 10000, sf::Color(0, 0, 0, 80));
		imgGrey.draw(bbox[0], bbox[1], 1000000);
	}
	else {
		if (hoverOver) {
			//pSpriteCollection->addRectDraw(bbox[0], bbox[1], bbox[2], bbox[3], 10000, sf::Color(200, 200, 200, 80));
			imgHover.draw(bbox[0], bbox[1], 1000000);
		}
		else {
			//pSpriteCollection->addRectDraw(bbox[0], bbox[1], bbox[2], bbox[3], 10000, sf::Color(255, 255, 255, 80));
			imgReady.draw(bbox[0], bbox[1], 1000000);
		}
	}
}

BuildButton::BuildButton(Console* _pConsole, SpriteCollection* _pSpriteCollection, Builder* _pBuilder, BuildType _buildType, glm::vec4 _bbox) :
	Button(_pConsole, _pSpriteCollection, ButtonType::build, _bbox) {
	buildType = _buildType;
	pBuilder = _pBuilder;
}

void BuildButton::press(){
	pBuilder->activate(buildType);
	pConsole->addCommand(commandCloseMenu);
}

void BuildButton::draw(){
	drawBox();
	if (buildType == BuildType::autoTurret) {
		pSpriteCollection->addTextDraw(2, bbox[0] + 16, bbox[1] + 16, 1000005, "Build Autoturret", 14, sf::Color(255, 255, 255, 255));
	} else 	if (buildType == BuildType::relay) {
		pSpriteCollection->addTextDraw(2, bbox[0] + 16, bbox[1] + 16, 1000005, "Build Relay", 14, sf::Color(255, 255, 255, 255));
	}
	else if (buildType == BuildType::generator) {
		pSpriteCollection->addTextDraw(2, bbox[0] + 16, bbox[1] + 16, 1000005, "Build Generator", 14, sf::Color(255, 255, 255, 255));
	}
}

void BuildButton::update(){
	if (pBuilder->checkResources(buildType)) {
		active = true;
	} else {
		active = false;
	}
}



StartGameButton::StartGameButton(Console* _pConsole, SpriteCollection* _pSpriteCollection, glm::vec4 _bbox) :
	Button(_pConsole, _pSpriteCollection, ButtonType::build, _bbox) {
	active = true;
}

void StartGameButton::press() {
	pConsole->addCommand(commandGoToGameplay);
}

void StartGameButton::draw() {
	drawBox();
	pSpriteCollection->addTextDraw(2, bbox[0] + 16, bbox[1] + 16, 1000005, "Start game", 14, sf::Color(255, 255, 255, 255));
}

MainMenuButton::MainMenuButton(Console* _pConsole, SpriteCollection* _pSpriteCollection, glm::vec4 _bbox) :
	Button(_pConsole, _pSpriteCollection, ButtonType::build, _bbox) {
	active = true;
}

void MainMenuButton::press() {
	pConsole->addCommand(commandGoToMainMenu);

}

void MainMenuButton::draw() {
	drawBox();
	pSpriteCollection->addTextDraw(2, bbox[0] + 16, bbox[1] + 16, 1000005, "Go to main menu", 14, sf::Color(255, 255, 255, 255));
}