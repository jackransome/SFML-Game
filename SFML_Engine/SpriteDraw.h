#pragma once
#include "Image.h"
#include <SFML\Graphics.hpp>

struct SpriteDraw {
	SpriteDraw() {}
	// Image constructor
	SpriteDraw(Image* _pSprite, float _x, float _y, float _z, float _scale) {
		scale = _scale;
		pImage = _pSprite;
		x = _x;
		y = _y;
		z = _z;
		w = 0;
		h = 0;
		r = 0;
		type = 0;
		color = sf::Color(0, 0, 0, 0);
	}
	// Image constructor with draw section
	SpriteDraw(Image* _pSprite, float _x, float _y, float _z, int _sX, int _sY, int _sW, int _sH, float _scale) {
		scale = _scale;
		pImage = _pSprite;
		x = _x;
		y = _y;
		z = _z;
		w = 0;
		h = 0;
		r = 0;
		type = 1;
		color = sf::Color(0, 0, 0, 0);
		sX = _sX;
		sY = _sY;
		sW = _sW;
		sH = _sH;
	}
	// Rectangle constructor
	SpriteDraw(float _x, float _y, float _w, float _h, float _z, sf::Color _color) {
		pImage = nullptr;
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		h = _h;
		r = 0;
		type = 2;
		color = _color;
	}
	// Circle constructor
	SpriteDraw(float _x, float _y, float _r, float _z, sf::Color _color) {
		pImage = nullptr;
		x = _x;
		y = _y;
		z = _z;
		w = 0;
		h = 0;
		r = _r;
		type = 3;
		color = _color;
	}
	// Text constructor
	SpriteDraw(int _fontIndex, float _x, float _y, float _z, std::string _string, int _fontSize, sf::Color _color) {
		pImage = nullptr;
		x = _x;
		y = _y;
		z = _z;
		string = _string;
		fontSize = _fontSize;
		color = _color;
		type = 4;
		fontIndex = _fontIndex;
	}
	Image* pImage;
	float x;
	float y;
	float z;
	float w = 0;
	float h = 0;
	float r = 0;
	int type; // 0 = image, 1 = image section, 2 = rectangle, 3 = circle, 4 = text
	sf::Color color;
	std::string string;
	int fontSize = 0;
	int fontIndex = 0;
	int sX = 0;
	int sY = 0;
	int sW = 0;
	int sH = 0;
	float scale;
};