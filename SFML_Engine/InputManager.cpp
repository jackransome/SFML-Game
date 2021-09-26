#include "InputManager.h"

InputManager::InputManager(){}

InputManager::InputManager(sf::RenderWindow* pwindow){
	pWindow = pwindow;
	keyStruct.w = false;
	keyStruct.a = false;
	keyStruct.s = false;
	keyStruct.d = false;
	keyStruct.space = false;
	keyStruct.escape = false;
}

void InputManager::update(){
	while (pWindow->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) pWindow->close();

		if (ev.type == sf::Event::KeyPressed) {
			if (ev.key.code == sf::Keyboard::W) {
				keyStruct.w = true;
			}
			if (ev.key.code == sf::Keyboard::A) {
				keyStruct.a = true;
			}
			if (ev.key.code == sf::Keyboard::S) {
				keyStruct.s = true;
			}
			if (ev.key.code == sf::Keyboard::D) {
				keyStruct.d = true;
			}
			if (ev.key.code == sf::Keyboard::Space) {
				keyStruct.space = true;
			}
			if (ev.key.code == sf::Keyboard::Escape) {
				keyStruct.escape = true;
			}
		}
		if (ev.type == sf::Event::KeyReleased) {
			if (ev.key.code == sf::Keyboard::W) {
				keyStruct.w = false;
			}
			if (ev.key.code == sf::Keyboard::A) {
				keyStruct.a = false;
			}
			if (ev.key.code == sf::Keyboard::S) {
				keyStruct.s = false;
			}
			if (ev.key.code == sf::Keyboard::D) {
				keyStruct.d = false;
			}
			if (ev.key.code == sf::Keyboard::Space) {
				keyStruct.space = false;
			}
			if (ev.key.code == sf::Keyboard::Escape) {
				keyStruct.escape = false;
			}
		}
	}
	sf::Vector2i localPosition = sf::Mouse::getPosition(*pWindow);
	mouseX = localPosition.x;
	mouseY = localPosition.y;
}

bool InputManager::isKeyDown(keys key){
	switch (key) {
	case w:
		return keyStruct.w;
		break;
	case a:
		return keyStruct.a;
		break;
	case s:
		return keyStruct.s;
		break;
	case d:
		return keyStruct.d;
		break;
	case space:
		return keyStruct.space;
		break;
	case escape:
		return keyStruct.escape;
		break;
	}
	std::cout << "key not implemented!\n";
	return false;
}
