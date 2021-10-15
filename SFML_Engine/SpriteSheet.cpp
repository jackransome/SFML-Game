#include "SpriteSheet.h"

SpriteSheet::SpriteSheet() {}

SpriteSheet::SpriteSheet(SpriteCollection* _pSpriteCollection, std::string _name, int _width, int _height, int _frames, float _scale) {
	scale = _scale;
	name = _name;
	width = _width;
	height = _height;
	frames = _frames;
	pSpriteCollection = _pSpriteCollection;
	pImage = pSpriteCollection->getPointerFromName(_name);
}

void SpriteSheet::run(){
	timer++;
	if (timer == changeTimer) {
		timer = 0;
	}
	if (timer == 0) {
		frame++;
		if (frame == frames) {
			if (doesReset) {
				frame = 0;
			}
			else {
				frame--;
			}

		}
	}

}

void SpriteSheet::draw(float x, float y, float z){
	pSpriteCollection->addImageDraw(pImage, x, y, z, frame * width, 0, width, height, scale);
}

void SpriteSheet::drawFrame(float x, float y, float z, int _frame) {
	pSpriteCollection->addImageDraw(pImage, x, y, z, _frame * width, 0, width, height, scale);
}

std::string SpriteSheet::getName() {
	return name;
}

void SpriteSheet::setDoesReset(bool _doesReset) {
	doesReset = _doesReset;
}

void SpriteSheet::setChangeTimer(int _changeTimer) {
	changeTimer = _changeTimer;
}

void SpriteSheet::reset() {
	timer = 0;
	frame = 0;
}

int SpriteSheet::getFrame() {
	return frame;
}
