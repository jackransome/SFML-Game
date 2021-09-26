#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum keys {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, leftArrow, rightArrow, upArrow, downArrow, escape, tab, backSpace, space, lControl, rControl, lShift, rShift, enter};

struct KeyStruct {
	bool a;
	bool b;
	bool c;
	bool d;
	bool e;
	bool f;
	bool g;
	bool h;
	bool i;
	bool j;
	bool k;
	bool l;
	bool m;
	bool n;
	bool o;
	bool p;
	bool q;
	bool r;
	bool s;
	bool t;
	bool u;
	bool v;
	bool w;
	bool x;
	bool y;
	bool z;
	bool leftArrow;
	bool rightArrow;
	bool upArrow;
	bool downArrow;
	bool escape;
	bool tab;
	bool backSpace;
	bool space;
	bool lControl;
	bool rControl;
	bool lShift;
	bool rShift;
	bool enter;
};

class InputManager {
public:
	InputManager();
	InputManager(sf::RenderWindow* pwindow);
	void update();
	bool isKeyDown(keys key);
	float mouseX;
	float mouseY;
private:
	sf::RenderWindow* pWindow;
	sf::Event ev;
	KeyStruct keyStruct;
};