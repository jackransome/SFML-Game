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
	keyStruct.r = false;
	keyStruct.f = false;
	keyStruct.t = false;
	keyStruct.y = false;
	keyStruct.lShift = false;
	keyStruct.lControl = false;
	lastKeyStruct = keyStruct;
	mouseL = false;
	mouseR = false;
}

void InputManager::update(){
	lastKeyStruct = keyStruct;
	while (pWindow->pollEvent(ev))
	{
		if (keyStruct.w > 0) {
			keyStruct.w++;
		}
		if (keyStruct.a > 0) {
			keyStruct.a++;
		}
		if (keyStruct.s > 0) {
			keyStruct.s++;
		}
		if (keyStruct.d > 0) {
			keyStruct.d++;
		}

		if (keyStruct.space > 0) {
			keyStruct.space++;
		}
		if (keyStruct.escape > 0) {
			keyStruct.escape++;
		}
		if (keyStruct.q > 0) {
			keyStruct.q++;
		}
		if (keyStruct.e > 0) {
			keyStruct.e++;
		}
		if (keyStruct.f > 0) {
			keyStruct.f++;
		}
		if (keyStruct.g > 0) {
			keyStruct.g++;
		}
		if (keyStruct.r > 0) {
			keyStruct.r++;
		}
		if (keyStruct.t > 0) {
			keyStruct.t++;
		}
		if (keyStruct.y > 0) {
			keyStruct.y++;
		}
		if (keyStruct.lShift > 0) {
			keyStruct.lShift++;
		}
		if (keyStruct.lControl > 0) {
			keyStruct.lControl++;
		}
		if (mouseL > 0) {
			mouseL++;
		}
		if (mouseR > 0) {
			mouseR++;
		}
		if (ev.type == sf::Event::Closed) pWindow->close();

		if (ev.type == sf::Event::KeyPressed) {
			if (ev.key.code == sf::Keyboard::W) {
				keyStruct.w = 1;
			}
			if (ev.key.code == sf::Keyboard::A) {
				keyStruct.a = 1;
			}
			if (ev.key.code == sf::Keyboard::S) {
				keyStruct.s = 1;
			}
			if (ev.key.code == sf::Keyboard::D) {
				keyStruct.d = 1;
			}
			if (ev.key.code == sf::Keyboard::Space) {
				keyStruct.space = 1;
			}
			if (ev.key.code == sf::Keyboard::Escape) {
				keyStruct.escape = 1;
			}
			if (ev.key.code == sf::Keyboard::Q) {
				keyStruct.q = 1;
			}
			if (ev.key.code == sf::Keyboard::E) {
				keyStruct.e = 1;
			}
			if (ev.key.code == sf::Keyboard::F) {
				keyStruct.f = 1;
			}
			if (ev.key.code == sf::Keyboard::G) {
				keyStruct.g = 1;
			}
			if (ev.key.code == sf::Keyboard::R) {
				keyStruct.r = 1;
			}
			if (ev.key.code == sf::Keyboard::T) {
				keyStruct.t = 1;
			}
			if (ev.key.code == sf::Keyboard::Y) {
				keyStruct.y = 1;
			}
			if (ev.key.code == sf::Keyboard::LShift) {
				keyStruct.lShift = 1;
			}
			if (ev.key.code == sf::Keyboard::LControl) {
				keyStruct.lControl = 1;
			}
		}
		if (ev.type == sf::Event::KeyReleased) {
			if (ev.key.code == sf::Keyboard::W) {
				keyStruct.w = 0;
			}
			if (ev.key.code == sf::Keyboard::A) {
				keyStruct.a = 0;
			}
			if (ev.key.code == sf::Keyboard::S) {
				keyStruct.s = 0;
			}
			if (ev.key.code == sf::Keyboard::D) {
				keyStruct.d = 0;
			}
			if (ev.key.code == sf::Keyboard::Space) {
				keyStruct.space = 0;
			}
			if (ev.key.code == sf::Keyboard::Escape) {
				keyStruct.escape = 0;
			}
			if (ev.key.code == sf::Keyboard::Q) {
				keyStruct.q = 0;
			}
			if (ev.key.code == sf::Keyboard::E) {
				keyStruct.e = 0;
			}
			if (ev.key.code == sf::Keyboard::F) {
				keyStruct.f = 0;
			}
			if (ev.key.code == sf::Keyboard::G) {
				keyStruct.g = 0;
			}
			if (ev.key.code == sf::Keyboard::R) {
				keyStruct.r = 0;
			}
			if (ev.key.code == sf::Keyboard::T) {
				keyStruct.t = 0;
			}
			if (ev.key.code == sf::Keyboard::Y) {
				keyStruct.y = 0;
			}
			if (ev.key.code == sf::Keyboard::LShift) {
				keyStruct.lShift = 0;
			}
			if (ev.key.code == sf::Keyboard::LControl) {
				keyStruct.lControl = 0;
			}
		}
		if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Left) {
				mouseL = 1;
			}
			if (ev.mouseButton.button == sf::Mouse::Right) {
				mouseR = 1;
			}
		}
		if (ev.type == sf::Event::MouseButtonReleased) {
			if (ev.mouseButton.button == sf::Mouse::Left) {
				mouseL = 0;
			}
			if (ev.mouseButton.button == sf::Mouse::Right) {
				mouseR = 0;
			}
		}
	}
	sf::Vector2i localPosition = sf::Mouse::getPosition(*pWindow);
	mouseX = localPosition.x;
	mouseY = localPosition.y;
}

int InputManager::isKeyDown(keys key){
	switch (key) {
	case w:
		return keyStruct.w;
	case a:
		return keyStruct.a;
	case s:
		return keyStruct.s;
	case d:
		return keyStruct.d;
	case space:
		return keyStruct.space;
	case escape:
		return keyStruct.escape;
	case q:
		return keyStruct.q;
	case e:
		return keyStruct.e;
	case f:
		return keyStruct.f;
	case g:
		return keyStruct.g;
	case r:
		return keyStruct.r;
	case t:
		return keyStruct.t;
	case y:
		return keyStruct.y;
	case lShift:
		return keyStruct.lShift;
	case lControl:
		return keyStruct.lControl;
	}
	std::cout << "key not implemented!\n";
	return false;
}

bool InputManager::onKeyDown(keys key) {
	switch (key) {
	case w:
		return !lastKeyStruct.w && keyStruct.w;
	case a:
		return !lastKeyStruct.a && keyStruct.a;
	case s:
		return !lastKeyStruct.s && keyStruct.s;
	case d:
		return !lastKeyStruct.d && keyStruct.d;
	case space:
		return !lastKeyStruct.space && keyStruct.space;
	case escape:
		return !lastKeyStruct.escape && keyStruct.escape;
	case q:
		return !lastKeyStruct.q && keyStruct.q;
	case e:
		return !lastKeyStruct.e && keyStruct.e;
	case f:
		return !lastKeyStruct.f && keyStruct.f;
	case g:
		return !lastKeyStruct.g && keyStruct.g;
	case r:
		return !lastKeyStruct.r && keyStruct.r;
	case t:
		return !lastKeyStruct.t && keyStruct.t;
	case y:
		return !lastKeyStruct.y && keyStruct.y;
	case lShift:
		return !lastKeyStruct.lShift && keyStruct.lShift;
	case lControl:
		return !lastKeyStruct.lControl && keyStruct.lControl;
	}
	std::cout << "key not implemented!\n";
	return false;
}

void InputManager::translateMouseCoords(float cameraX, float cameraY){
	translatedMouseX = mouseX + cameraX;
	translatedMouseY = mouseY + cameraY;
}
