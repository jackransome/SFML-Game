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

void SpriteStack::draw(float x, float y, float z, float rotation){
	for (int i = 0; i < frames; i++) {
		pSpriteCollection->addRotatedImageDraw(pTexture, x, y - i*scale, z + scale * height, i * width, 0, width, height, scale, rotation);
	}
}

void SpriteStack::draw(float x, float y, float z, float rotation, float rx, float ry) {
	for (int i = 0; i < frames; i++) {
		pSpriteCollection->addRotatedImageDraw(pTexture, x, y - i * scale, y + scale * height, i * width, 0, width, height, scale, rotation, rx, ry);
	}
}

void SpriteStack::draw(float x, float y, float z, float rotation, std::string shader) {
	for (int i = 0; i < frames; i++) {
		pSpriteCollection->addRotatedImageDraw(pTexture, x, y - i * scale, z + scale * height, i * width, 0, width, height, scale, rotation);
		pSpriteCollection->addShaderToLast("shader1");
		pSpriteCollection->addShaderToLast(shader);
	}
}

void SpriteStack::draw(float x, float y, float z, float rotation, float rx, float ry, std::string shader) {
	for (int i = 0; i < frames; i++) {
		pSpriteCollection->addRotatedImageDraw(pTexture, x, y - i * scale, y + scale * height, i * width, 0, width, height, scale, rotation, rx, ry);
		pSpriteCollection->addShaderToLast("shader1");
		pSpriteCollection->addShaderToLast(shader);
	}
	
}

void SpriteStack::setOpacity(float _opacity){
	opacity = _opacity;
}
