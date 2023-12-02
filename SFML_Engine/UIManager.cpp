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
		for (int i = 0; i < panes.size(); i++) {
			if (CollisionDetection::pointRectangleIntersect(glm::vec2(pInputManager->mouseX, pInputManager->mouseY), panes[i])) {
				pInputManager->disableMouseButtons();
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
		addButton(ButtonType::startGame, glm::vec4(50, 500, 250, 50));
		state = 0;
		break;
	case MenuType::pause:
		addButton(ButtonType::goToMain, glm::vec4(50, 500, 250, 50));
		state = 1;
		break;
	case MenuType::builder:
		addPane(glm::vec4(25, 475, 300, 300));
		addButton(ButtonType::build, BuildType::autoTurret, glm::vec4(50,500,250,50));
		addButton(ButtonType::build, BuildType::relay, glm::vec4(50, 600, 250, 50));
		addButton(ButtonType::build, BuildType::generator, glm::vec4(50, 700, 250, 50));
		state = 2;
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

void UIManager::drawPane(glm::vec4 pane){
	pSpriteCollection->addImageDrawCut(pSpriteCollection->getPointerFromName("menu_pane"), pane.x, pane.y, 500000, 0, 0, pane[2], pane[3], 1, 0.1);
}

void UIManager::clear(){
	buttons.clear();
	panes.clear();
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
		for (int i = 0; i < panes.size(); i++) {
			drawPane(panes[i]);
		}
	}
	pSpriteCollection->setAbsoluteMode(false);
}

int UIManager::getState(){
	return state;
}

void UIManager::addButton(ButtonType type, glm::vec4 bbox){
	if (type == ButtonType::startGame) {
		buttons.push_back(std::make_unique<StartGameButton>(pConsole, pSpriteCollection, bbox));
	} else if (type == ButtonType::goToMain) {
		buttons.push_back(std::make_unique<MainMenuButton>(pConsole, pSpriteCollection, bbox));
	}	else if (type == ButtonType::back) {
		//UNFINISHED
		buttons.push_back(std::make_unique<StartGameButton>(pConsole, pSpriteCollection, bbox));
	}
}

void UIManager::addButton(ButtonType type, BuildType buildType, glm::vec4 bbox) {

	buttons.push_back(std::make_unique<BuildButton>(pConsole, pSpriteCollection, pBuilder, buildType, bbox));
}

void UIManager::addPane(glm::vec4 bbox){
	panes.push_back(bbox);
}
