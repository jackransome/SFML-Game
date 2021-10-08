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
	keyStruct.q = false;
	keyStruct.e = false;
	keyStruct.f = false;
	keyStruct.lShift = false;
	keyStruct.lControl = false;
	mouseL = false;
	mouseR = false;
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
			if (ev.key.code == sf::Keyboard::Q) {
				keyStruct.q = true;
			}
			if (ev.key.code == sf::Keyboard::E) {
				keyStruct.e = true;
			}
			if (ev.key.code == sf::Keyboard::F) {
				keyStruct.f = true;
			}
			if (ev.key.code == sf::Keyboard::LShift) {
				keyStruct.lShift = true;
			}
			if (ev.key.code == sf::Keyboard::LControl) {
				keyStruct.lControl = true;
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
			if (ev.key.code == sf::Keyboard::Q) {
				keyStruct.q = false;
			}
			if (ev.key.code == sf::Keyboard::E) {
				keyStruct.e = false;
			}
			if (ev.key.code == sf::Keyboard::F) {
				keyStruct.f = false;
			}
			if (ev.key.code == sf::Keyboard::LShift) {
				keyStruct.lShift = false;
			}
			if (ev.key.code == sf::Keyboard::LControl) {
				keyStruct.lControl = false;
			}
		}
		if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Left) {
				mouseL = true;
			}
			if (ev.mouseButton.button == sf::Mouse::Right) {
				mouseR = true;
			}
		}
		if (ev.type == sf::Event::MouseButtonReleased) {
			if (ev.mouseButton.button == sf::Mouse::Left) {
				mouseL = false;
			}
			if (ev.mouseButton.button == sf::Mouse::Right) {
				mouseR = false;
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
	case q:
		return keyStruct.q;
		break;
	case e:
		return keyStruct.e;
		break;
	case f:
		return keyStruct.f;
		break;
	case lShift:
		return keyStruct.lShift;
		break;
	case lControl:
		return keyStruct.lControl;
		break;
	}
	std::cout << "key not implemented!\n";
	return false;
}

void InputManager::translateMouseCoords(float cameraX, float cameraY){
	translatedMouseX = mouseX + cameraX;
	translatedMouseY = mouseY + cameraY;
}
