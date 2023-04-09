#include "InputManager.h"

InputManager::InputManager(){}

InputManager::InputManager(sf::RenderWindow* pwindow, int *screenW, int *screenH){
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
	keyStruct.g = false;
	keyStruct.t = false;
	keyStruct.y = false;
	keyStruct.u = false;
	keyStruct.upArrow = false;
	keyStruct.downArrow = false;
	keyStruct.lShift = false;
	keyStruct.lControl = false;
	keyStruct.n1 = false;
	keyStruct.n2 = false;
	keyStruct.n3 = false;
	keyStruct.n4 = false;
	keyStruct.n5 = false;
	keyStruct.n6 = false;
	keyStruct.n7 = false;
	keyStruct.n8 = false;
	keyStruct.n9 = false;
	keyStruct.n0 = false;
	keyStruct.mouseL = false;
	keyStruct.mouseR = false;
	lastKeyStruct = keyStruct;
	pScreenW = screenW;
	pScreenH = screenH;
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
		if (keyStruct.u > 0) {
			keyStruct.u++;
		}
		if (keyStruct.n1 > 0) {
			keyStruct.n1++;
		}
		if (keyStruct.n2 > 0) {
			keyStruct.n2++;
		}
		if (keyStruct.n3 > 0) {
			keyStruct.n3++;
		}
		if (keyStruct.n4 > 0) {
			keyStruct.n4++;
		}
		if (keyStruct.n5 > 0) {
			keyStruct.n5++;
		}
		if (keyStruct.n6 > 0) {
			keyStruct.n6++;
		}
		if (keyStruct.n7 > 0) {
			keyStruct.n7++;
		}
		if (keyStruct.n8 > 0) {
			keyStruct.n8++;
		}
		if (keyStruct.n9 > 0) {
			keyStruct.n9++;
		}
		if (keyStruct.n0 > 0) {
			keyStruct.n0++;
		}
		if (keyStruct.lShift > 0) {
			keyStruct.lShift++;
		}
		if (keyStruct.lControl > 0) {
			keyStruct.lControl++;
		}
		//if (keyStruct.upArrow > 0) {
		//	keyStruct.upArrow++;
		//}
		//if (keyStruct.downArrow > 0) {
		//	keyStruct.downArrow++;
		//}
		if (keyStruct.mouseL > 0) {
			keyStruct.mouseL++;
		}
		if (keyStruct.mouseR > 0) {
			keyStruct.mouseR++;
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
			if (ev.key.code == sf::Keyboard::U) {
				keyStruct.u = 1;
			}
			if (ev.key.code == sf::Keyboard::Up) {
				keyStruct.upArrow = 1;
			}
			if (ev.key.code == sf::Keyboard::Down) {
				keyStruct.downArrow = 1;
			}
			if (ev.key.code == sf::Keyboard::LShift) {
				keyStruct.lShift = 1;
			}
			if (ev.key.code == sf::Keyboard::LControl) {
				keyStruct.lControl = 1;
			}
			if (ev.key.code == sf::Keyboard::Num1) {
				keyStruct.n1 = 1;
			}
			if (ev.key.code == sf::Keyboard::Num2) {
				keyStruct.n2 = 1;
			}
			if (ev.key.code == sf::Keyboard::Num3) {
				keyStruct.n3 = 1;
			}
			if (ev.key.code == sf::Keyboard::Num4) {
				keyStruct.n4 = 1;
			}
			if (ev.key.code == sf::Keyboard::Num5) {
				keyStruct.n5 = 1;
			}
			if (ev.key.code == sf::Keyboard::Num6) {
				keyStruct.n6 = 1;
			}
			if (ev.key.code == sf::Keyboard::Num7) {
				keyStruct.n7 = 1;
			}
			if (ev.key.code == sf::Keyboard::Num8) {
				keyStruct.n8 = 1;
			}
			if (ev.key.code == sf::Keyboard::Num9) {
				keyStruct.n9 = 1;
			}
			if (ev.key.code == sf::Keyboard::Num0) {
				keyStruct.n0 = 1;
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
			if (ev.key.code == sf::Keyboard::U) {
				keyStruct.u = 0;
			}
			if (ev.key.code == sf::Keyboard::LShift) {
				keyStruct.lShift = 0;
			}
			if (ev.key.code == sf::Keyboard::LControl) {
				keyStruct.lControl = 0;
			}
			if (ev.key.code == sf::Keyboard::Up) {
				keyStruct.upArrow = 0;
			}
			if (ev.key.code == sf::Keyboard::Down) {
				keyStruct.downArrow = 0;
			}
			if (ev.key.code == sf::Keyboard::Num1) {
				keyStruct.n1 = 0;
			}
			if (ev.key.code == sf::Keyboard::Num2) {
				keyStruct.n2 = 0;
			}
			if (ev.key.code == sf::Keyboard::Num3) {
				keyStruct.n3 = 0;
			}
			if (ev.key.code == sf::Keyboard::Num4) {
				keyStruct.n4 = 0;
			}
			if (ev.key.code == sf::Keyboard::Num5) {
				keyStruct.n5 = 0;
			}
			if (ev.key.code == sf::Keyboard::Num6) {
				keyStruct.n6 = 0;
			}
			if (ev.key.code == sf::Keyboard::Num7) {
				keyStruct.n7 = 0;
			}
			if (ev.key.code == sf::Keyboard::Num8) {
				keyStruct.n8 = 0;
			}
			if (ev.key.code == sf::Keyboard::Num9) {
				keyStruct.n9 = 0;
			}
			if (ev.key.code == sf::Keyboard::Num0) {
				keyStruct.n0 = 0;
			}
		}
		if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Left) {
				keyStruct.mouseL = 1;
			}
			if (ev.mouseButton.button == sf::Mouse::Right) {
				keyStruct.mouseR = 1;
			}
		}
		if (ev.type == sf::Event::MouseButtonReleased) {
			if (ev.mouseButton.button == sf::Mouse::Left) {
				keyStruct.mouseL = 0;
			}
			if (ev.mouseButton.button == sf::Mouse::Right) {
				keyStruct.mouseR = 0;
			}
		}
		if (ev.type == sf::Event::Resized) {
			pWindow->setView(sf::View(sf::FloatRect(0, 0, ev.size.width, ev.size.height)));
			//pWindow->setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
			*pScreenW = ev.size.width;
			*pScreenH = ev.size.height;
			//pWindow->setSize(sf::Vector2u(ev.size.height, ev.size.width));
			//pWindow->setView(sf::View(sf::Vector2f((float)ev.size.height/2,(float)ev.size.width/2), sf::Vector2f(ev.size.height, ev.size.width)));
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
	case u:
		return keyStruct.u;
	case n1:
		return keyStruct.n1;
	case n2:
		return keyStruct.n2;
	case n3:
		return keyStruct.n3;
	case n4:
		return keyStruct.n4;
	case n5:
		return keyStruct.n5;
	case n6:
		return keyStruct.n6;
	case n7:
		return keyStruct.n7;
	case n8:
		return keyStruct.n8;
	case n9:
		return keyStruct.n9;
	case n0:
		return keyStruct.n0;
	case lShift:
		return keyStruct.lShift;
	case lControl:
		return keyStruct.lControl;
	case upArrow:
		return keyStruct.upArrow;
	case downArrow:
		return keyStruct.downArrow;
	case mouseL:
		return keyStruct.mouseL;
	case mouseR:
		return keyStruct.mouseR;
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
	case u:
		return !lastKeyStruct.u && keyStruct.u;
	case n1:
		return !lastKeyStruct.n1 && keyStruct.n1;
	case n2:
		return !lastKeyStruct.n2 && keyStruct.n2;
	case n3:
		return !lastKeyStruct.n3 && keyStruct.n3;
	case n4:
		return !lastKeyStruct.n4 && keyStruct.n4;
	case n5:
		return !lastKeyStruct.n5 && keyStruct.n5;
	case n6:
		return !lastKeyStruct.n6 && keyStruct.n6;
	case n7:
		return !lastKeyStruct.n7 && keyStruct.n7;
	case n8:
		return !lastKeyStruct.n8 && keyStruct.n8;
	case n9:
		return !lastKeyStruct.n9 && keyStruct.n9;
	case n0:
		return !lastKeyStruct.n0 && keyStruct.n0;
	case lShift:
		return !lastKeyStruct.lShift && keyStruct.lShift;
	case lControl:
		return !lastKeyStruct.lControl && keyStruct.lControl;
	case upArrow:
		return !lastKeyStruct.upArrow && keyStruct.upArrow;
	case downArrow:
		return !lastKeyStruct.downArrow && keyStruct.downArrow;
	case mouseL:
		return !lastKeyStruct.mouseL && keyStruct.mouseL;
	case mouseR:
		return !lastKeyStruct.mouseR && keyStruct.mouseR;
	}
	std::cout << "key not implemented!\n";
	return false;
}

void InputManager::translateMouseCoords(float cameraX, float cameraY){
	translatedMouseX = mouseX + cameraX;
	translatedMouseY = mouseY + cameraY;
}
