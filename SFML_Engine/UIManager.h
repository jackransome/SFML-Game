#pragma once

#include "InputManager.h"
#include "Button.h"
#include <vector>

enum class MenuType {
	main, pause, builder
};

class UIManager {
public:
	UIManager() {};
	UIManager(Console* _pConsole, SpriteCollection* _pSpriteCollection, InputManager* _pInputManager, Builder* _pBuilder);
	void update();
	void loadNewMenu(MenuType menuType);
	
	void unloadMenu();
	void setState(int _state);
	void setActive(bool _active);
	bool getActive();
	void draw();
	int getState();
private:
	void loadNewMenu(int _state);
	void addButton(ButtonType type, glm::vec4 bbox);
	void addButton(ButtonType type, BuildType buildType, glm::vec4 bbox);
	Console* pConsole;
	std::vector<std::unique_ptr<Button>> buttons;
	SpriteCollection* pSpriteCollection;
	InputManager* pInputManager;
	Builder* pBuilder;
	bool active = true;
	int state = -1; //0 = mainmenu, 1 = buildmenu, 2 = pausemenu
	//ADD PANES FOR ORGANIZATION,, AESTHETIC< AND NO CLICK THRU
};