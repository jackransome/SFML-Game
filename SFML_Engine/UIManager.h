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
	void setActive(bool _active);
	void draw();
private:
	void addButton(ButtonType type, glm::vec4 bbox);
	void addButton(ButtonType type, BuildType buildType, glm::vec4 bbox);
	Console* pConsole;
	std::vector<std::unique_ptr<Button>> buttons;
	SpriteCollection* pSpriteCollection;
	InputManager* pInputManager;
	Builder* pBuilder;
	bool active = false;
};