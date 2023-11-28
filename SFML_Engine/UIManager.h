#pragma once

#include "InputManager.h"
#include "Button.h"
#include <vector>
class UIManager {
public:
	UIManager(Console _console, SpriteCollection* _pSpriteCollection, InputManager* _pInputManager);
	void update();
	void loadNewMenu();
private:
	void addButton();
	Console console;
	std::vector<Button> buttons;
	SpriteCollection* pSpriteCollection;
	InputManager* pInputManager;
};