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
			if (buttons[i]->getActive()) {
				glm::vec4 bbox = buttons[i]->getBbox();
				if (CollisionDetection::pointRectangleIntersect(glm::vec2(pInputManager->mouseX, pInputManager->mouseY), bbox)) {
					buttons[i]->setHover(true);
					if (pInputManager->onKeyDown(mouseL)) {
						buttons[i]->press();
					}
				}
				else {
					buttons[i]->setHover(false);
				}
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
		addButton(ButtonType::build, BuildType::turret, glm::vec4(500,500,500,100));
		break;
	}
}

void UIManager::setActive(bool _active){
	active = _active;
}

void UIManager::draw(){
	if (active) {
		for (int i = 0; i < buttons.size(); i++) {
			buttons[i]->draw();
		}
	}
}

void UIManager::addButton(ButtonType type, glm::vec4 bbox){

	buttons.push_back(std::make_unique<BuildButton>(pSpriteCollection, pBuilder, BuildType::teleporter, glm::vec4(0)));
}

void UIManager::addButton(ButtonType type, BuildType buildType, glm::vec4 bbox) {

	buttons.push_back(std::make_unique<BuildButton>(pSpriteCollection, pBuilder, buildType, bbox));
}
