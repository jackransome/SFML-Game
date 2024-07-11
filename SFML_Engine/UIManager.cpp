#include "UIManager.h"
#include "CollisionDetection.h"

UIManager::UIManager(Console* _pConsole, SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Builder* _pBuilder, PowerManager* _pPowerManager, int* _pScreenW, int* _pScreenH) {
	pConsole = _pConsole;
	pSpriteCollection = _pSpriteCollection;
	pInputManager = _pInputManager;
	pBuilder = _pBuilder;
	pPowerManager = _pPowerManager;
	pScreenW = _pScreenW;
	pScreenH = _pScreenH;
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
		if (pInputManager->onKeyDown(mouseL)) {
			int index = -1;
			for (int i = 0; i < inventoryPanes.size(); i++) {
				if ((index = inventoryPanes[i]->getIndexFromMouse(pInputManager->mouseX, pInputManager->mouseY)) != -1 && index < inventoryPanes[i]->getInventory()->getSlotsUsed()) {
					//set taken
					inventoryPanes[i]->setTaken(index);
					//get index pointer
					taken = true;
					takenIndex = index;
					takenFrom = i;
					takenItem = inventoryPanes[i]->getInventory()->getItem(index);
				}
			}
		}
		if (taken && pInputManager->onKeyUp(mouseL)) {
			int index = -1;
			for (int i = 0; i < inventoryPanes.size(); i++) {
				if ((index = inventoryPanes[i]->getIndexFromMouse(pInputManager->mouseX, pInputManager->mouseY)) != -1) {
					if (inventoryPanes[i]->getInventory()->addItem(takenItem, index)) {
						//if same inventory and index is before the taken index, increment taken index before removing
						if (i == takenFrom && index < takenIndex) {
							takenIndex++;
						}
						inventoryPanes[takenFrom]->getInventory()->removeItem(takenIndex);
						break;
					}
				}
			}
			taken = false;
			inventoryPanes[takenFrom]->resetTaken();
		}
	}
}

void UIManager::loadNewMenu(MenuType menuType){
	currentMenu = menuType;
	clear();
	switch (menuType) {
	case MenuType::main:
		addButton(ButtonType::startGame, glm::vec4(50, 500, 250, 50));
		break;
	case MenuType::pause:
		addButton(ButtonType::goToMain, glm::vec4(50, 500, 250, 50));
		break;
	case MenuType::builder:
		addPane(glm::vec4(25, 475, 500, 700));
		for (int i = 0; i < static_cast<int>(BuildType::count); i++) {
			addBuildbuttonWithCost(static_cast<BuildType>(i), glm::vec4(50, 500 + 100*i, 250, 50));
		}
		addButton(ButtonType::connect, glm::vec4(150, 1100, 250, 50));
		break;
	case MenuType::end:
		addButton(ButtonType::goToMain, glm::vec4(50, 500, 250, 50));
		break;
	case MenuType::singleInventory:
		addInventoryPane((*pScreenW / 2) - (invCellSize * inventory1->getCellsWidth()) / 2, (*pScreenH / 2) - (invCellSize * inventory1->getCellsHeight()) / 2, inventory1);
		addInventoryPane((*pScreenW / 2) - (invCellSize * toolbar->getCellsWidth()) / 2, (*pScreenH / 2) + (invCellSize * (1+inventory1->getCellsHeight())) / 2, toolbar);
		break;
	case MenuType::doubleInventory:
		int centerX = *pScreenW / 2;
		int centerY = *pScreenH / 2;
		addInventoryPane(centerX - (invCellSize / 2) - invCellSize * inventory1->getCellsWidth(), centerY - (invCellSize * inventory1->getCellsHeight()) / 2, inventory1);
		addInventoryPane(centerX + (invCellSize / 2), centerY - (invCellSize * inventory2->getCellsHeight()) / 2, inventory2);
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

void UIManager::drawInventory(Inventory* _inventory, int _x, int _y) {
	int sizeMinusGap = invCellSize - 2 * invCellGap;
	Item* tempItem;
	for (int i = 0; i < _inventory->getSlots(); i++) {
		int x = _x + (i % 4) * invCellSize;
		int y = _y + floor(float(i) / 4.0f) * invCellSize;
		pSpriteCollection->addImageDrawCut(pSpriteCollection->getPointerFromName("menu_pane"), x + invCellGap, y + invCellGap, 500000, 0, 0, sizeMinusGap, invCellBorder, 1, 0.2);
		pSpriteCollection->addImageDrawCut(pSpriteCollection->getPointerFromName("menu_pane"), x + invCellGap, y + invCellGap, 500000, 0, 0, invCellBorder, sizeMinusGap, 1, 0.2);
		if (_inventory->getSlotsUsed() > i) {
			tempItem = _inventory->getItem(i);
			tempItem->draw(x + invCellSize/2, y + invCellSize / 2, 500000, 2);
		}
	}
}

void UIManager::drawPane(glm::vec4 pane){
	pSpriteCollection->addImageDrawCut(pSpriteCollection->getPointerFromName("menu_pane"), pane.x, pane.y, 500000, 0, 0, pane[2], pane[3], 1, 0.1);
}

void UIManager::clear(){
	buttons.clear();
	panes.clear();
	textboxes.clear();
	inventoryPanes.clear();
}

void UIManager::unloadMenu(){
	clear();
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
		for (int i = 0; i < inventoryPanes.size(); i++) {
			inventoryPanes[i]->draw();
		}
		if (taken) {
			takenItem->draw(pInputManager->mouseX, pInputManager->mouseY, 500000, 2);
		}
	}
	pSpriteCollection->setAbsoluteMode(false);
}

void UIManager::addButton(ButtonType _type, glm::vec4 _bbox){
	if (_type == ButtonType::startGame) {
		buttons.push_back(std::make_unique<StartGameButton>(pConsole, pSpriteCollection, _bbox));
	} else if (_type == ButtonType::goToMain) {
		buttons.push_back(std::make_unique<MainMenuButton>(pConsole, pSpriteCollection, _bbox));
	}	else if (_type == ButtonType::connect) {
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

void UIManager::addInventoryPane(int _x, int _y, Inventory* _pInventory) {
	inventoryPanes.push_back(new InventoryPane(_x, _y, _pInventory, pSpriteCollection));
}

void UIManager::addPane(glm::vec4 bbox){
	panes.push_back(bbox);
}

void UIManager::setInventorys(Inventory* _inventory1, Inventory* _inventory2) {
	inventory1 = _inventory1;
	inventory2 = _inventory2;
}

void UIManager::setToolbar(Inventory* _toolbar) {
	toolbar = _toolbar;
}

MenuType UIManager::getCurrentMenu() {
	return currentMenu;
}
