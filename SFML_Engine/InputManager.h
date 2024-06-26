#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Camera.h"

enum keys {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, n1, n2, n3, n4, n5, n6, n7, n8, n9, n0, leftArrow, rightArrow, upArrow, downArrow, escape, tab, backSpace, space, lControl, rControl, lShift, rShift, enter, mouseL, mouseR, mouseM, mouseW};

struct KeyStruct {
	int a; int b; int c; int d; int e; int f; int g; int h; int i; int j; int k; int l; int m; int n; int o; int p; int q; int r; int s; int t; int u;
	int v; int w; int x; int y; int z; int leftArrow; int rightArrow; int upArrow; int downArrow; int escape; int tab; int backSpace; int space; int lControl;
	int rControl; int lShift; int rShift; int enter; int n1; int n2; int n3; int n4; int n5; int n6; int n7; int n8; int n9; int n0; int mouseL; int mouseR; int mouseM; int mouseW;
};

class InputManager {
public:
	InputManager();
	InputManager(sf::RenderWindow* pwindow, int* screenW, int* screenH);
	void update();
	int isKeyDown(keys key);
	bool onKeyDown(keys key);
	bool onKeyUp(keys key);
	void translateMouseCoords(float cameraX, float cameraY);
	float mouseX;
	float mouseY;
	float translatedMouseX;
	float translatedMouseY;
	int getMenuMode();
	void setMenuMode(int mode);
	void disableMouseButtons();
	void setScale(float _scale);
private:
	float scale = 1;
	bool disableMB = false;
	int menuMode = 0;
	int* pScreenW;
	int* pScreenH;
	sf::RenderWindow* pWindow;
	sf::Event ev;
	KeyStruct keyStruct;
	KeyStruct lastKeyStruct;
};