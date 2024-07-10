#pragma once

#include "InputManager.h"
#include "Button.h"
#include "Textbox.h"
#include <vector>
#include "Inventory.h"
enum class MenuType {
	main, pause, builder, end
};

class UIManager {
public:
	UIManager() {};
	UIManager(Console* _pConsole, SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Builder* _pBuilder, PowerManager* _pPowerManager);
	void update();
	void loadNewMenu(MenuType menuType);
	void unloadMenu();
	void toggleState(MenuType newMenuType);
	void setState(int _state);
	void setActive(bool _active);
	bool getActive();
	void draw();
	int getState();
	
private:
	void drawInventory(); //109 109 109
	void loadNewMenu(int _state);
	void drawPane(glm::vec4 pane);
	void clear();
	void addButton(ButtonType type, glm::vec4 bbox);
	void addBuildbuttonWithCost(BuildType _type, glm::vec4 _bbox);
	void addButton(ButtonType type, BuildType buildType, glm::vec4 bbox);
	void addTextBox(TextboxType type, glm::vec4 _bbox, std::string _text);
	void addPane(glm::vec4 bbox);
	Console* pConsole;
	std::vector<std::unique_ptr<Button>> buttons;
	std::vector<glm::vec4> panes;
	std::vector< std::unique_ptr<Textbox>> textboxes;
	SpriteCollection* pSpriteCollection;
	InputManager* pInputManager;
	Builder* pBuilder;
	PowerManager* pPowerManager;
	bool active = true;
	MenuType currentMenu = MenuType::main;
	int state = -1; //0 = mainmenu, 1 = buildmenu, 2 = pausemenu
	//ADD PANES FOR ORGANIZATION,, AESTHETIC< AND NO CLICK THRU
};