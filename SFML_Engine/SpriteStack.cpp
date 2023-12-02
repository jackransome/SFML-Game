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
		if (rasterizeMode) {
			rasterize();
		}
		firstDraw = false;
	}
	if (_rotation != rotation) {
		x = _x;
		y = _y;
		z = _z;

		rotation = _rotation;
		if (rasterizeMode) {
			rasterize();
		}
	}
	else {
		x = _x;
		y = _y;
		z = _z;
	}
	if (rasterizeMode) {
		pSpriteCollection->drawRasterization(&rasterization, z, x - size / 2, y - size / 2, size, size);
	}
	else {
		drawNormally();
	}
}

void SpriteStack::draw(float _x, float _y, float _z, float _rotation, float _rx, float _ry) {
	if (firstDraw) {
		if (rasterizeMode) {
			rasterize();
		}
		firstDraw = false;
	}
	if (_rotation != rotation || _rx != rx || _ry != ry) {
		x = _x;
		y = _y;
		z = _z;
		rotation = _rotation;
		rx = _rx;
		ry = _ry;
		if (rasterizeMode) {
			rasterize();
		}
	}
	else {
		x = _x;
		y = _y;
		z = _z;
	}
	if (rasterizeMode) {
		pSpriteCollection->drawRasterization(&rasterization, z, x - size / 2, y - size / 2, size, size);
	}
	else {
		drawNormally();
	}
}

void SpriteStack::draw(float _x, float _y, float _z, float _rotation, std::string shader) {
	if (firstDraw) {
		if (rasterizeMode) {
			rasterize();
		}
		firstDraw = false;
	}
	if (_rotation != rotation) {
		x = _x;
		y = _y;
		z = _z;
		rotation = _rotation;
		if (rasterizeMode) {
			rasterize();
		}
	}
	else {
		x = _x;
		y = _y;
		z = _z;
	}
	if (rasterizeMode) {
		pSpriteCollection->drawRasterization(&rasterization, z, x - size / 2, y - size / 2, size, size);
	}
	else {
		drawNormally();
	}
}

void SpriteStack::draw(float _x, float _y, float _z, float _rotation, float _rx, float _ry, std::string shader) {
	if (firstDraw) {
		if (rasterizeMode) {
			rasterize();
		}
		firstDraw = false;
	}
	if (_rotation != rotation || _rx != rx || _ry != ry) {
		x = _x;
		y = _y;
		z = _z;
		rotation = _rotation;
		rx = _rx;
		ry = _ry;
		if (rasterizeMode) {
			rasterize();
		}
	}
	else {
		x = _x;
		y = _y;
		z = _z;
	}
	if (rasterizeMode) {
		pSpriteCollection->drawRasterization(&rasterization, y + scale * height, x - size / 2, y - size / 2, size, size);
	}
	else {
		drawNormally();
	}
}

void SpriteStack::setOpacity(float _opacity){
	opacity = _opacity;
}

void SpriteStack::setRasterizeMode(bool mode){
	//set to false for things that are constantly rotating
	rasterizeMode = mode;
}

void SpriteStack::drawUpTo(float x, float y, float z, float rotation, int frame){
	if (frame > frames) {
		frame = frames;
	}
	for (int i = 0; i < frame; i++) {
		pSpriteCollection->addRotatedImageDrawCut(pTexture, x, y - i * scale, z + scale * height, i * width, 0, width, height, scale, rotation);
	}
}

void SpriteStack::drawUpToPercent(float x, float y, float z, float rotation, float percent){
	if (percent > 1) {
		percent = 1;
	}
	if (percent < 0) {
		percent = 0;
	}
	int frame = percent * frames;
	for (int i = 0; i < frame; i++) {
		pSpriteCollection->addRotatedImageDrawCut(pTexture, x, y - i * scale, z + scale * height, i * width, 0, width, height, scale, rotation);
	}
}

void SpriteStack::rasterize() {
	for (int i = 0; i < frames; i++) {
		pSpriteCollection->addRotatedImageDrawCut(pTexture, x, y - i * scale, z + scale * height, i * width, 0, width, height, scale, rotation);
	}
	size = (width > height + frames ? width : height + frames) * scale * 4;

	rasterization = pSpriteCollection->rasterizeStack(frames, size, size);
}

void SpriteStack::drawNormally(){
	for (int i = 0; i < frames; i++) {
		pSpriteCollection->addRotatedImageDrawCut(pTexture, x, y - i * scale, z + scale * height, i * width, 0, width, height, scale, rotation);
	}
}
