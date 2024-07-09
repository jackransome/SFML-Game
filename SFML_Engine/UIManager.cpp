#include "UIManager.h"
#include "CollisionDetection.h"

UIManager::UIManager(Console* _pConsole, SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Builder* _pBuilder, PowerManager* _pPowerManager) {
	pConsole = _pConsole;
	pSpriteCollection = _pSpriteCollection;
	pInputManager = _pInputManager;
	pBuilder = _pBuilder;
	pPowerManager = _pPowerManager;
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
	if (panes.size() > 0) {
		panes.clear();
	}
	if (textboxes.size() > 0) {
		textboxes.clear();
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
		addPane(glm::vec4(25, 475, 500, 700));
		for (int i = 0; i < static_cast<int>(BuildType::count); i++) {
			addBuildbuttonWithCost(static_cast<BuildType>(i), glm::vec4(50, 500 + 100*i, 250, 50));
		}
		addButton(ButtonType::connect, glm::vec4(150, 1100, 250, 50));
		state = 2;
		break;
	case MenuType::end:
		addButton(ButtonType::goToMain, glm::vec4(50, 500, 250, 50));
		state = 3;
		break;
	}
}

void UIManager::addBuildbuttonWithCost(BuildType _type, glm::vec4 _bbox){
	glm::vec4 temp1 = _bbox;
	glm::vec4 temp2 = _bbox;
	temp1.x += 100;
	temp2.y += 16;
	addButton(ButtonType::build, _type, temp1);
	addTextBox(TextboxType::display, temp2, std::to_string(pBuilder->getScrapNeeded(_type)) + " | " + std::to_string(pBuilder->getComponentsNeeded(_type)));
}

void UIManager::loadNewMenu(int _state) {
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
	case 3:
		loadNewMenu(MenuType::end);
		break;
	}
	state = _state;
}

void UIManager::drawPane(glm::vec4 pane){
	pSpriteCollection->addImageDrawCut(pSpriteCollection->getPointerFromName("menu_pane"), pane.x, pane.y, 500000, 0, 0, pane[2], pane[3], 1, 0.1);
}

void UIManager::clear(){
	buttons.clear();
	panes.clear();
	textboxes.clear();
}

void UIManager::unloadMenu(){
	buttons.clear();
	panes.clear();
	textboxes.clear();
}

void UIManager::toggleState(MenuType newMenuType){
	if (!active) {
		active = true;
		loadNewMenu(newMenuType);
	}
	else {
		active = false;
	}
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
		for (int i = 0; i < textboxes.size(); i++) {
			textboxes[i]->draw();
		}
	}
	pSpriteCollection->setAbsoluteMode(false);
}

int UIManager::getState(){
	return state;
}

void UIManager::addButton(ButtonType _type, glm::vec4 _bbox){
	if (_type == ButtonType::startGame) {
		buttons.push_back(std::make_unique<StartGameButton>(pConsole, pSpriteCollection, _bbox));
	} else if (_type == ButtonType::goToMain) {
		buttons.push_back(std::make_unique<MainMenuButton>(pConsole, pSpriteCollection, _bbox));
	}	else if (_type == ButtonType::connect) {
		//UNFINISHED
		buttons.push_back(std::make_unique<ConnectButton>(pConsole, pSpriteCollection, pPowerManager, _bbox));
	}
}

void UIManager::addButton(ButtonType _type, BuildType _buildType, glm::vec4 _bbox) {

	buttons.push_back(std::make_unique<BuildButton>(pConsole, pSpriteCollection, pBuilder, _buildType, _bbox));
}

void UIManager::addTextBox(TextboxType _type, glm::vec4 _bbox, std::string _text) {
	if (_type == TextboxType::display) {
		textboxes.push_back(std::make_unique<DisplayTextbox>(pConsole, pSpriteCollection, _bbox, _text));
	}
	else {
		std::cout << "TextboxType does not exist\n";
	}
}

void UIManager::addPane(glm::vec4 bbox){
	panes.push_back(bbox);
}
