#include "SpriteStack.h"

SpriteStack::SpriteStack(){}

SpriteStack::SpriteStack(SpriteCollection* _pSpriteCollection, std::string _name, int _width, int _height, int _frames, float _scale) {
	scale = _scale;
	width = _width;
	height = _height;
	frames = _frames;
	pSpriteCollection = _pSpriteCollection;
	pTexture = pSpriteCollection->getPointerFromName(_name);

}

void SpriteStack::draw(float _x, float _y, float _z, float _rotation){
	if (firstDraw) {
		rasterize();
		firstDraw = false;
	}
	if (_rotation != rotation) {
		x = _x;
		y = _y;
		z = _z;

		rotation = _rotation;
		rasterize();
	}
	else {
		x = _x;
		y = _y;
		z = _z;
	}
	pSpriteCollection->drawRasterization(&rasterization, y + scale * height, x - size / 2, y - size / 2, size, size);
}

void SpriteStack::draw(float _x, float _y, float _z, float _rotation, float _rx, float _ry) {
	if (firstDraw) {
		rasterize();
		firstDraw = false;
	}
	if (_rotation != rotation || _rx != rx || _ry != ry) {
		x = _x;
		y = _y;
		z = _z;
		rotation = _rotation;
		rx = _rx;
		ry = _ry;
		rasterize();
	}
	else {
		x = _x;
		y = _y;
		z = _z;
	}
	pSpriteCollection->drawRasterization(&rasterization, y + scale * height, x - size / 2, y - size / 2, size, size);
}

void SpriteStack::draw(float _x, float _y, float _z, float _rotation, std::string shader) {
	if (firstDraw) {
		rasterize();
		firstDraw = false;
	}
	if (_rotation != rotation) {
		x = _x;
		y = _y;
		z = _z;
		rotation = _rotation;
		rasterize();
	}
	else {
		x = _x;
		y = _y;
		z = _z;
	}
	pSpriteCollection->drawRasterization(&rasterization, y + scale * height, x-size/2, y - size / 2, size, size);
}

void SpriteStack::draw(float _x, float _y, float _z, float _rotation, float _rx, float _ry, std::string shader) {
	if (firstDraw) {
		rasterize();
		firstDraw = false;
	}
	if (_rotation != rotation || _rx != rx || _ry != ry) {
		x = _x;
		y = _y;
		z = _z;
		rotation = _rotation;
		rx = _rx;
		ry = _ry;
		rasterize();
	}
	else {
		x = _x;
		y = _y;
		z = _z;
	}

	pSpriteCollection->drawRasterization(&rasterization, y + scale * height, x - size / 2, y - size / 2, size, size);
}

void SpriteStack::setOpacity(float _opacity){
	opacity = _opacity;
}

void SpriteStack::rasterize() {
	for (int i = 0; i < frames; i++) {
		pSpriteCollection->addRotatedImageDrawCut(pTexture, x, y - i * scale, z + scale * height, i * width, 0, width, height, scale, rotation);
	}
	size = (width > height + frames ? width : height + frames) * scale * 4;

	rasterization = pSpriteCollection->rasterizeStack(frames, size, size);
}
