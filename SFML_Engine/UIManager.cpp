#include "UIManager.h"
#include "CollisionDetection.h"

UIManager::UIManager(Console* _pConsole, SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Builder* _pBuilder) {
	pConsole = _pConsole;
	pSpriteCollection = _pSpriteCollection;
	pInputManager = _pInputManager;
	pBuilder = _pBuilder;
}

void UIManager::update(){
	if (active) {
		for (int i = 0; i < buttons.size(); i++) {
			buttons[i]->update();
			
			glm::vec4 bbox = buttons[i]->getBbox();
			if (CollisionDetection::pointRectangleIntersect(glm::vec2(pInputManager->mouseX, pInputManager->mouseY), bbox)) {
				if (buttons[i]->getActive()) {
					if (!buttons[i]->getHover()) {
						pConsole->addCommand(commandPlaySound, "menu_hover", 0.03);
					}
					buttons[i]->setHover(true);
					if (pInputManager->onKeyDown(mouseL)) {
						pConsole->addCommand(commandPlaySound, "menu_click", 0.6);
						buttons[i]->press();
					}
				}
				pInputManager->disableMouseButtons();
			}
			else {
				buttons[i]->setHover(false);
			}
		}
	}
}

void UIManager::loadNewMenu(MenuType menuType){
	if (buttons.size() > 0) {
		buttons.clear();
	}
	switch (menuType) {
	case MenuType::main:
		break;
	case MenuType::pause:
		break;
	case MenuType::builder:
		addButton(ButtonType::build, BuildType::turret, glm::vec4(50,500,250,50));
		addButton(ButtonType::build, BuildType::relay, glm::vec4(50, 600, 250, 50));
		break;
	}
}
void UIManager::loadNewMenu(int _state) {
	if (buttons.size() > 0) {
		buttons.clear();
	}
	switch (_state) {
	case 0:
		loadNewMenu(MenuType::main);
		break;
	case 1:
		loadNewMenu(MenuType::pause);
		break;
	case 2:
		loadNewMenu(MenuType::builder);
		break;
	}
}

void UIManager::unloadMenu(){
	buttons.clear();
}

void UIManager::setState(int _state){
	if (state != _state) {
		loadNewMenu(_state);
	}
	state = _state;
}

void UIManager::setActive(bool _active){
	active = _active;
}

bool UIManager::getActive(){
	return active;
}

void UIManager::draw(){
	pSpriteCollection->setAbsoluteMode(true);
	if (active) {
		for (int i = 0; i < buttons.size(); i++) {
			buttons[i]->draw();
		}
	}
	pSpriteCollection->setAbsoluteMode(false);
}

int UIManager::getState(){
	return state;
}

void UIManager::addButton(ButtonType type, glm::vec4 bbox){

	buttons.push_back(std::make_unique<BuildButton>(pConsole, pSpriteCollection, pBuilder, BuildType::teleporter, glm::vec4(0)));
}

void UIManager::addButton(ButtonType type, BuildType buildType, glm::vec4 bbox) {

	buttons.push_back(std::make_unique<BuildButton>(pConsole, pSpriteCollection, pBuilder, buildType, bbox));
}
