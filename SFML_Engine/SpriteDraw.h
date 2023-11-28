#pragma once
#include <SFML\Graphics.hpp>
#include "Shader_Pipeline_Classes.h"
struct SpriteDraw {
	SpriteDraw() {}
	// Image constructor
	SpriteDraw(TextureWrapper* _pTexture, float _x, float _y, float _z, float _scale) {
		scale = _scale;
		pTexture = _pTexture;
		x = _x;
		y = _y;
		z = _z;
		w = 0;
		h = 0;
		r = 0;
		type = 0;
		color = sf::Color(0, 0, 0, 0);
	}

	//rasterized texture constructor
	SpriteDraw(sf::Texture* _pRaster, float _x, float _y, float _z, float _w, float _h) {
		pRaster = _pRaster;
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		h = _h;
		type = 5;
	}

	SpriteDraw(TextureWrapper* _pTexture, float _x, float _y, float _z, float _scale, float _opacity) {
		scale = _scale;
		pTexture = _pTexture;
		x = _x;
		y = _y;
		z = _z;
		w = 0;
		h = 0;
		r = 0;
		type = 0;
		color = sf::Color(0, 0, 0, 0);
		opacity = _opacity;
	}

	// Image constructor with draw section
	SpriteDraw(TextureWrapper* _pTexture, float _x, float _y, float _z, int _sX, int _sY, int _sW, int _sH, float _scale) {
		scale = _scale;
		pTexture = _pTexture;
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
	// Image constructor with draw section
	SpriteDraw(TextureWrapper* _pTexture, float _x, float _y, float _z, int _sX, int _sY, int _sW, int _sH, float _scale, float _opacity) {
		scale = _scale;
		pTexture = _pTexture;
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
		opacity = _opacity;
	}
	// Rectangle constructor
	SpriteDraw(float _x, float _y, float _w, float _h, float _z, sf::Color _color) {
		pTexture = nullptr;
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		h = _h;
		r = 0;
		type = 2;
		color = _color;
	}
	// Rectangle constructor
	SpriteDraw(float _x, float _y, float _w, float _h, float _z, sf::Color _color, float _opacity) {
		pTexture = nullptr;
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		h = _h;
		r = 0;
		type = 2;
		color = _color;
		opacity = _opacity;
	}
	// Circle constructor
	SpriteDraw(float _x, float _y, float _r, float _z, sf::Color _color) {
		pTexture = nullptr;
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
		pTexture = nullptr;
		x = _x;
		y = _y;
		z = _z;
		string = _string;
		fontSize = _fontSize;
		color = _color;
		type = 4;
		fontIndex = _fontIndex;
	}
	void setRotation(float _rotation) {
		rotation = _rotation;
	}
	void setRPoint(float _rx, float _ry) {
		rx = _rx;
		ry = _ry;
		rotationPoint = true;
	}
	void setFullBright() {
		fullBright = true;
	}
	void setPipeline(int index) {
		pipelineIndex = index;
	}

	int pipelineIndex = 0;
	TextureWrapper* pTexture;
	sf::Texture* pRaster;
	float x;
	float y;
	float z;
	float w = 0;
	float h = 0;
	float r = 0;
	float rx;
	float ry;
	bool rotationPoint = false;
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
	float opacity = 1;
	float rotation = 0;
	bool fullBright = false;
	bool absolute = false;
};