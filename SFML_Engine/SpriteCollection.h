#pragma once
#include "Sprite.h"
#include <vector>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Graphics.h"
#include <iostream>

struct SpriteDraw {
	SpriteDraw() {}
	// Image constructor
	SpriteDraw(Sprite* _pSprite, float _x, float _y, float _z) {
		
		pSprite = _pSprite;
		x = _x;
		y = _y;
		z = _z;
		w = 0;
		h = 0;
		r = 0;
		type = 0;
		color = sf::Color(0,0,0,0);
	}
	// Rectangle constructor
	SpriteDraw(float _x, float _y, float _w, float _h, float _z, sf::Color _color) {
		pSprite = nullptr;
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		h = _h;
		r = 0;
		type = 1;
		color = _color;
	}
	// Circle constructor
	SpriteDraw(float _x, float _y, float _r, float _z, sf::Color _color) {
		pSprite = nullptr;
		x = _x;
		y = _y;
		z = _z;
		w = 0;
		h = 0;
		r = _r;
		type = 2;
		color = _color;
	}
	// Text constructor
	SpriteDraw(int _fontIndex, float _x, float _y, float _z, std::string _string, int _fontSize, sf::Color _color) {
		pSprite = nullptr;
		x = _x;
		y = _y;
		z = _z;
		string = _string;
		fontSize = _fontSize;
		color = _color;
		type = 3;
		fontIndex = _fontIndex;
	}
	Sprite* pSprite;
	float x;
	float y;
	float z;
	float w = 0;
	float h = 0;
	float r = 0;
	int type; // 0 = image, 1 = rectangle, 2 = circle, 3 = text
	sf::Color color;
	std::string string;
	int fontSize = 0;
	int fontIndex = 0;
};

class SpriteCollection {
public:
	SpriteCollection();
	SpriteCollection(sf::RenderWindow* pwindow, Graphics* pgraphics);
	void createSprite(std::string name, std::string path, int _width, int _height, int _frames, float _scale);
	void createSprite(std::string name, std::string path, float _scale);
	Sprite* getPointerFromName(std::string name);
	void setUseCamera(bool _useCamera);
	void setPCamera(Camera *_pCamera);
	void setOrderZ(bool _orderZ);
	void addSpriteDraw(Sprite* pSprite, float x, float y, float z);
	void addRectDraw(float x, float y, float w, float h, float z, sf::Color);
	void addCircleDraw(float x, float y, float r, float z, sf::Color);
	void addAbsoluteSpriteDraw(Sprite* pSprite, float x, float y, float z);
	void addAbsoluteRectDraw(float x, float y, float w, float h, float z, sf::Color);
	void addAbsoluteCircleDraw(float x, float y, float r, float z, sf::Color);
	void addTextDraw(int fontIndex, float x, float y, float z, std::string string, int fontSize, sf::Color color);
	void addAbsoluteTextDraw(int fontIndex, float x, float y, float z, std::string string, int _fontSize, sf::Color _color);
	void drawAll();
	void drawText(int fontIndex, float x, float y, std::string string, int _fontSize, sf::Color _color);
	void addFont(std::string name);
private:
	void clearSpriteDraws();
	void orderByZ();
	sf::RenderWindow *pWindow;
	Graphics *pGraphics;
	std::vector<Sprite*> sprites;
	int maxSpriteDraws = 1000;
	int maxAbsoluteSpriteDraws = 1000;
	SpriteDraw *spriteDraws[1000];
	SpriteDraw *absoluteSpriteDraws[1000];
	int currentDrawIndex = 0;
	int currentAbsoluteDrawIndex = 0;
	bool useCamera = false;
	Camera *pCamera;
	std::vector<sf::Font> fonts;
	bool orderZ = false;
};