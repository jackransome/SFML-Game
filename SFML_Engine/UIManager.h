#pragma once

#include "InputManager.h"
#include "Button.h"
#include "Textbox.h"
#include "InventoryPane.h"
#include <vector>
#include "Inventory.h"
enum class MenuType {
	main, pause, builder, singleInventory, doubleInventory, end
};

class UIManager {
public:
	UIManager() {};
	UIManager(Console* _pConsole, SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Builder* _pBuilder, PowerManager* _pPowerManager, int* _pScreenW, int* _pScreenH);
	void update();
	void loadNewMenu(MenuType menuType);
	void unloadMenu();
	void toggleState(MenuType newMenuType);
	void setActive(bool _active);
	bool getActive();
	void draw();
	void setInventorys(Inventory* _inventory1, Inventory* _inventory2); 
	void setToolbar(Inventory* _toolbar);
	MenuType getCurrentMenu();
private:
	void drawInventory(Inventory* _inventory, int x, int y); //109 109 109
	void drawPane(glm::vec4 pane);
	void clear();
	void addButton(ButtonType type, glm::vec4 bbox);
	void addBuildbuttonWithCost(BuildType _type, glm::vec4 _bbox);
	void addButton(ButtonType type, BuildType buildType, glm::vec4 bbox);
	void addTextBox(TextboxType type, glm::vec4 _bbox, std::string _text);
	void addInventoryPane(int _x, int _y, Inventory* _pInventory);
	void addPane(glm::vec4 bbox);
	Console* pConsole;
	std::vector<std::unique_ptr<Button>> buttons;
	std::vector<glm::vec4> panes;
	std::vector<std::unique_ptr<Textbox>> textboxes;
	std::vector<InventoryPane*> inventoryPanes;
	SpriteCollection* pSpriteCollection;
	InputManager* pInputManager;
	Builder* pBuilder;
	PowerManager* pPowerManager;
	bool active = true;
	MenuType currentMenu = MenuType::main;
	Inventory* inventory1 = nullptr;
	Inventory* inventory2 = nullptr;
	Inventory* toolbar = nullptr;
	int* pScreenW;
	int* pScreenH;
	int invCellSize = 96;
	int invCellGap = 4;
	int invCellBorder = 8;
	Item* takenItem;
	int takenIndex = -1;
	bool taken = false;
	int takenFrom = -1;
};