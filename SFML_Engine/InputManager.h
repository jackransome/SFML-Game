#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum keys {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, leftArrow, rightArrow, upArrow, downArrow, escape, tab, backSpace, space, lControl, rControl, lShift, rShift, enter};

struct KeyStruct {
	int a; int b; int c; int d; int e; int f; int g; int h; int i; int j; int k; int l; int m; int n; int o; int p; int q; int r; int s; int t; int u;
	int v; int w; int x; int y; int z; int leftArrow; int rightArrow; int upArrow; int downArrow; int escape; int tab; int backSpace; int space; int lControl;
	int rControl; int lShift; int rShift; int enter;
};

class InputManager {
public:
	InputManager();
	InputManager(sf::RenderWindow* pwindow);
	void update();
	int isKeyDown(keys key);
	int wasKeyDown(keys key);
	void translateMouseCoords(float cameraX, float cameraY);
	float mouseX;
	float mouseY;
	float translatedMouseX;
	float translatedMouseY;
	int mouseL;
	int mouseR;
private:
	sf::RenderWindow* pWindow;
	sf::Event ev;
	KeyStruct keyStruct;
	KeyStruct lastKeyStruct;
};