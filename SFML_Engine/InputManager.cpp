#include "InputManager.h"

InputManager::InputManager(){}

InputManager::InputManager(sf::RenderWindow* pwindow, int *screenW, int *screenH){
	pWindow = pwindow;
	keyStruct.a = false;
	keyStruct.b = false;
	keyStruct.c = false;
	keyStruct.d = false;
	keyStruct.e = false;
	keyStruct.f = false;
	keyStruct.g = false;
	keyStruct.h = false;
	keyStruct.i = false;
	keyStruct.j = false;
	keyStruct.k = false;
	keyStruct.l = false;
	keyStruct.m = false;
	keyStruct.n = false;
	keyStruct.o = false;
	keyStruct.p = false;
	keyStruct.q = false;
	keyStruct.r = false;
	keyStruct.s = false;
	keyStruct.t = false;
	keyStruct.u = false;
	keyStruct.v = false;
	keyStruct.w = false;
	keyStruct.x = false;
	keyStruct.y = false;
	keyStruct.z = false;
	keyStruct.space = false;
	keyStruct.escape = false;
	keyStruct.upArrow = false;
	keyStruct.downArrow = false;
	keyStruct.lShift = false;
	keyStruct.lControl = false;
	keyStruct.mouseL = false;
	keyStruct.mouseR = false;
	keyStruct.mouseM = false;
	lastKeyStruct = keyStruct;
	pScreenW = screenW;
	pScreenH = screenH;
}

void InputManager::update(){
	disableMB = false;
	lastKeyStruct = keyStruct;
	while (pWindow->pollEvent(ev))
	{
		if (keyStruct.a > 0) {
			keyStruct.a++;
		}
		if (keyStruct.b > 0) {
			keyStruct.b++;
		}
		if (keyStruct.c > 0) {
			keyStruct.c++;
		}
		if (keyStruct.d > 0) {
			keyStruct.d++;
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
		if (keyStruct.h > 0) {
			keyStruct.h++;
		}
		if (keyStruct.i > 0) {
			keyStruct.i++;
		}
		if (keyStruct.j > 0) {
			keyStruct.j++;
		}
		if (keyStruct.k > 0) {
			keyStruct.k++;
		}
		if (keyStruct.l > 0) {
			keyStruct.l++;
		}
		if (keyStruct.m > 0) {
			keyStruct.m++;
		}
		if (keyStruct.n > 0) {
			keyStruct.n++;
		}
		if (keyStruct.o > 0) {
			keyStruct.o++;
		}
		if (keyStruct.p > 0) {
			keyStruct.p++;
		}
		if (keyStruct.q > 0) {
			keyStruct.q++;
		}
		if (keyStruct.r > 0) {
			keyStruct.r++;
		}
		if (keyStruct.s > 0) {
			keyStruct.s++;
		}
		if (keyStruct.t > 0) {
			keyStruct.t++;
		}
		if (keyStruct.u > 0) {
			keyStruct.u++;
		}
		if (keyStruct.v > 0) {
			keyStruct.v++;
		}
		if (keyStruct.w > 0) {
			keyStruct.w++;
		}
		if (keyStruct.x > 0) {
			keyStruct.x++;
		}
		if (keyStruct.y > 0) {
			keyStruct.y++;
		}
		if (keyStruct.z > 0) {
			keyStruct.z++;
		}
		if (keyStruct.space > 0) {
			keyStruct.space++;
		}
		if (keyStruct.escape > 0) {
			keyStruct.escape++;
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
		if (keyStruct.mouseM > 0) {
			keyStruct.mouseM++;
		}
		if (ev.type == sf::Event::Closed) pWindow->close();

		if (ev.type == sf::Event::KeyPressed) {
			if (ev.key.code == sf::Keyboard::A) {
				keyStruct.a = 1;
			}
			if (ev.key.code == sf::Keyboard::B) {
				keyStruct.b = 1;
			}
			if (ev.key.code == sf::Keyboard::C) {
				keyStruct.c = 1;
			}
			if (ev.key.code == sf::Keyboard::D) {
				keyStruct.d = 1;
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
			if (ev.key.code == sf::Keyboard::H) {
				keyStruct.h = 1;
			}
			if (ev.key.code == sf::Keyboard::I) {
				keyStruct.i = 1;
			}
			if (ev.key.code == sf::Keyboard::J) {
				keyStruct.j = 1;
			}
			if (ev.key.code == sf::Keyboard::K) {
				keyStruct.k = 1;
			}
			if (ev.key.code == sf::Keyboard::L) {
				keyStruct.l = 1;
			}
			if (ev.key.code == sf::Keyboard::M) {
				keyStruct.m = 1;
			}
			if (ev.key.code == sf::Keyboard::N) {
				keyStruct.n = 1;
			}
			if (ev.key.code == sf::Keyboard::O) {
				keyStruct.o = 1;
			}
			if (ev.key.code == sf::Keyboard::P) {
				keyStruct.p = 1;
			}
			if (ev.key.code == sf::Keyboard::Q) {
				keyStruct.q = 1;
			}
			if (ev.key.code == sf::Keyboard::R) {
				keyStruct.r = 1;
			}
			if (ev.key.code == sf::Keyboard::S) {
				keyStruct.s = 1;
			}
			if (ev.key.code == sf::Keyboard::T) {
				keyStruct.t = 1;
			}
			if (ev.key.code == sf::Keyboard::U) {
				keyStruct.u = 1;
			}
			if (ev.key.code == sf::Keyboard::V) {
				keyStruct.v = 1;
			}
			if (ev.key.code == sf::Keyboard::W) {
				keyStruct.w = 1;
			}
			if (ev.key.code == sf::Keyboard::X) {
				keyStruct.x = 1;
			}
			if (ev.key.code == sf::Keyboard::Y) {
				keyStruct.y = 1;
			}
			if (ev.key.code == sf::Keyboard::Z) {
				keyStruct.z = 1;
			}

			if (ev.key.code == sf::Keyboard::Space) {
				keyStruct.space = 1;
			}
			if (ev.key.code == sf::Keyboard::Escape) {
				keyStruct.escape = 1;
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
			if (ev.key.code == sf::Keyboard::A) {
				keyStruct.a = 0;
			}
			if (ev.key.code == sf::Keyboard::B) {
				keyStruct.b = 0;
			}
			if (ev.key.code == sf::Keyboard::C) {
				keyStruct.c = 0;
			}
			if (ev.key.code == sf::Keyboard::D) {
				keyStruct.d = 0;
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
			if (ev.key.code == sf::Keyboard::H) {
				keyStruct.h = 0;
			}
			if (ev.key.code == sf::Keyboard::I) {
				keyStruct.i = 0;
			}
			if (ev.key.code == sf::Keyboard::J) {
				keyStruct.j = 0;
			}
			if (ev.key.code == sf::Keyboard::K) {
				keyStruct.k = 0;
			}
			if (ev.key.code == sf::Keyboard::L) {
				keyStruct.l = 0;
			}
			if (ev.key.code == sf::Keyboard::M) {
				keyStruct.m = 0;
			}
			if (ev.key.code == sf::Keyboard::N) {
				keyStruct.n = 0;
			}
			if (ev.key.code == sf::Keyboard::O) {
				keyStruct.o = 0;
			}
			if (ev.key.code == sf::Keyboard::P) {
				keyStruct.p = 0;
			}
			if (ev.key.code == sf::Keyboard::Q) {
				keyStruct.q = 0;
			}
			if (ev.key.code == sf::Keyboard::R) {
				keyStruct.r = 0;
			}
			if (ev.key.code == sf::Keyboard::S) {
				keyStruct.s = 0;
			}
			if (ev.key.code == sf::Keyboard::T) {
				keyStruct.t = 0;
			}
			if (ev.key.code == sf::Keyboard::U) {
				keyStruct.u = 0;
			}
			if (ev.key.code == sf::Keyboard::V) {
				keyStruct.v = 0;
			}
			if (ev.key.code == sf::Keyboard::W) {
				keyStruct.w = 0;
			}
			if (ev.key.code == sf::Keyboard::X) {
				keyStruct.x = 0;
			}
			if (ev.key.code == sf::Keyboard::Y) {
				keyStruct.y = 0;
			}
			if (ev.key.code == sf::Keyboard::Z) {
				keyStruct.z = 0;
			}

			if (ev.key.code == sf::Keyboard::Space) {
				keyStruct.space = 0;
			}
			if (ev.key.code == sf::Keyboard::Escape) {
				keyStruct.escape = 0;
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
			if (ev.mouseButton.button == sf::Mouse::Middle) {
				keyStruct.mouseM = 1;
			}
		}
		if (ev.type == sf::Event::MouseButtonReleased) {
			if (ev.mouseButton.button == sf::Mouse::Left) {
				keyStruct.mouseL = 0;
			}
			if (ev.mouseButton.button == sf::Mouse::Right) {
				keyStruct.mouseR = 0;
			}
			if (ev.mouseButton.button == sf::Mouse::Middle) {
				keyStruct.mouseM = 0;
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
	case a:
		return keyStruct.a;
	case b:
		return keyStruct.b;
	case c:
		return keyStruct.c;
	case d:
		return keyStruct.d;
	case e:
		return keyStruct.e;
	case f:
		return keyStruct.f;
	case g:
		return keyStruct.g;
	case h:
		return keyStruct.h;
	case i:
		return keyStruct.i;
	case j:
		return keyStruct.j;
	case k:
		return keyStruct.k;
	case l:
		return keyStruct.l;
	case m:
		return keyStruct.m;
	case n:
		return keyStruct.n;
	case o:
		return keyStruct.o;
	case p:
		return keyStruct.p;
	case q:
		return keyStruct.q;
	case r:
		return keyStruct.r;
	case s:
		return keyStruct.s;
	case t:
		return keyStruct.t;
	case u:
		return keyStruct.u;
	case v:
		return keyStruct.v;
	case w:
		return keyStruct.w;
	case x:
		return keyStruct.x;
	case y:
		return keyStruct.y;
	case z:
		return keyStruct.z;
	case space:
		return keyStruct.space;
	case escape:
		return keyStruct.escape;
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
		if (disableMB) return 0;
		return keyStruct.mouseL;
	case mouseR:
		if (disableMB) return 0;
		return keyStruct.mouseR;
	case mouseM:
		if (disableMB) return 0;
		return keyStruct.mouseM;
	}
	std::cout << "key not implemented!\n";
	return false;
}

bool InputManager::onKeyDown(keys key) {
	switch (key) {
	case a:
		return !lastKeyStruct.a && keyStruct.a;
	case b:
		return !lastKeyStruct.b && keyStruct.b;
	case c:
		return !lastKeyStruct.c && keyStruct.c;
	case d:
		return !lastKeyStruct.d && keyStruct.d;
	case e:
		return !lastKeyStruct.e && keyStruct.e;
	case f:
		return !lastKeyStruct.f && keyStruct.f;
	case g:
		return !lastKeyStruct.g && keyStruct.g;
	case h:
		return !lastKeyStruct.h && keyStruct.h;
	case i:
		return !lastKeyStruct.i && keyStruct.i;
	case j:
		return !lastKeyStruct.j && keyStruct.j;
	case k:
		return !lastKeyStruct.k && keyStruct.k;
	case l:
		return !lastKeyStruct.l && keyStruct.l;
	case m:
		return !lastKeyStruct.m && keyStruct.m;
	case n:
		return !lastKeyStruct.n && keyStruct.n;
	case o:
		return !lastKeyStruct.o && keyStruct.o;
	case p:
		return !lastKeyStruct.p && keyStruct.p;
	case q:
		return !lastKeyStruct.q && keyStruct.q;
	case r:
		return !lastKeyStruct.r && keyStruct.r;
	case s:
		return !lastKeyStruct.s && keyStruct.s;
	case t:
		return !lastKeyStruct.t && keyStruct.t;
	case u:
		return !lastKeyStruct.u && keyStruct.u;
	case v:
		return !lastKeyStruct.v && keyStruct.v;
	case w:
		return !lastKeyStruct.w && keyStruct.w;
	case x:
		return !lastKeyStruct.x && keyStruct.x;
	case y:
		return !lastKeyStruct.y && keyStruct.y;
	case z:
		return !lastKeyStruct.z && keyStruct.z;
	case space:
		return !lastKeyStruct.space && keyStruct.space;
	case escape:
		return !lastKeyStruct.escape && keyStruct.escape;
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
		if (disableMB) return 0;
		return !lastKeyStruct.mouseL && keyStruct.mouseL;
	case mouseR:
		if (disableMB) return 0;
		return !lastKeyStruct.mouseR && keyStruct.mouseR;
	case mouseM:
		if (disableMB) return 0;
		return !lastKeyStruct.mouseM && keyStruct.mouseM;
	}
	std::cout << "key not implemented!\n";
	return false;
}

bool InputManager::onKeyUp(keys key){
	switch (key) {
	case a:
		return lastKeyStruct.a && !keyStruct.a;
	case b:
		return lastKeyStruct.b && !keyStruct.b;
	case c:
		return lastKeyStruct.c && !keyStruct.c;
	case d:
		return lastKeyStruct.d && !keyStruct.d;
	case e:
		return lastKeyStruct.e && !keyStruct.e;
	case f:
		return lastKeyStruct.f && !keyStruct.f;
	case g:
		return lastKeyStruct.g && !keyStruct.g;
	case h:
		return lastKeyStruct.h && !keyStruct.h;
	case i:
		return lastKeyStruct.i && !keyStruct.i;
	case j:
		return lastKeyStruct.j && !keyStruct.j;
	case k:
		return lastKeyStruct.k && !keyStruct.k;
	case l:
		return lastKeyStruct.l && !keyStruct.l;
	case m:
		return lastKeyStruct.m && !keyStruct.m;
	case n:
		return lastKeyStruct.n && !keyStruct.n;
	case o:
		return lastKeyStruct.o && !keyStruct.o;
	case p:
		return lastKeyStruct.p && !keyStruct.p;
	case q:
		return lastKeyStruct.q && !keyStruct.q;
	case r:
		return lastKeyStruct.r && !keyStruct.r;
	case s:
		return lastKeyStruct.s && !keyStruct.s;
	case t:
		return lastKeyStruct.t && !keyStruct.t;
	case u:
		return lastKeyStruct.u && !keyStruct.u;
	case v:
		return lastKeyStruct.v && !keyStruct.v;
	case w:
		return lastKeyStruct.w && !keyStruct.w;
	case x:
		return lastKeyStruct.x && !keyStruct.x;
	case y:
		return lastKeyStruct.y && !keyStruct.y;
	case z:
		return lastKeyStruct.z && !keyStruct.z;
	case space:
		return lastKeyStruct.space && !keyStruct.space;
	case escape:
		return lastKeyStruct.escape && !keyStruct.escape;
	case n1:
		return lastKeyStruct.n1 && !keyStruct.n1;
	case n2:
		return lastKeyStruct.n2 && !keyStruct.n2;
	case n3:
		return lastKeyStruct.n3 && !keyStruct.n3;
	case n4:
		return lastKeyStruct.n4 && !keyStruct.n4;
	case n5:
		return lastKeyStruct.n5 && !keyStruct.n5;
	case n6:
		return lastKeyStruct.n6 && !keyStruct.n6;
	case n7:
		return lastKeyStruct.n7 && !keyStruct.n7;
	case n8:
		return lastKeyStruct.n8 && !keyStruct.n8;
	case n9:
		return lastKeyStruct.n9 && !keyStruct.n9;
	case n0:
		return lastKeyStruct.n0 && !keyStruct.n0;
	case lShift:
		return lastKeyStruct.lShift && !keyStruct.lShift;
	case lControl:
		return lastKeyStruct.lControl && !keyStruct.lControl;
	case upArrow:
		return lastKeyStruct.upArrow && !keyStruct.upArrow;
	case downArrow:
		return lastKeyStruct.downArrow && !keyStruct.downArrow;
	case mouseL:
		if (disableMB) return 0;
		return lastKeyStruct.mouseL && !keyStruct.mouseL;
	case mouseR:
		if (disableMB) return 0;
		return lastKeyStruct.mouseR && !keyStruct.mouseR;
	case mouseM:
		if (disableMB) return 0;
		return lastKeyStruct.mouseM && !keyStruct.mouseM;
	}
	std::cout << "key not implemented!\n";
	return false;
}

void InputManager::translateMouseCoords(float cameraX, float cameraY){
	translatedMouseX = mouseX + cameraX;
	translatedMouseY = mouseY + cameraY;
}

int InputManager::getMenuMode() {
	return menuMode;
}

void InputManager::setMenuMode(int mode){
	menuMode = mode;
}

void InputManager::disableMouseButtons(){
	disableMB = true;
}
