#include "Sprite.h"

Sprite::Sprite() {}

Sprite::Sprite(sf::RenderWindow* pwindow, std::string _name, std::string path, float _scale){
	scale = _scale;
	pWindow = pwindow; 
	name = _name;
	sprite = sf::Sprite();
	texture = sf::Texture();
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}

Sprite::Sprite(sf::RenderWindow* pwindow, std::string _name, std::string path, int _width, int _height, int _frames, float _scale) {
	scale = _scale;
	pWindow = pwindow;
	name = _name;
	texture.loadFromFile(path);
	width = _width;
	height = _height;
	frames = _frames;
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}

void Sprite::run(){
	if (frames > 1) {
		frame++;
	}
	if (frame == frames) {
		frame = 0;
	}
}

void Sprite::draw(float x, float y){
	if (frames > 1) {
		sprite.setTextureRect(sf::IntRect(frame * width, 0, width, height));
	}
	sprite.setPosition(x, y);
	pWindow->draw(sprite);
}

void Sprite::drawFrame(float x, float y, int _frame) {
	sprite.setTextureRect(sf::IntRect(_frame * width, 0, width, height));
	sprite.setPosition(x, y);
	pWindow->draw(sprite);
}

void Sprite::setScale(float w, float h) {
	sprite.setScale(w, h);
}

std::string Sprite::getName() {
	return name;
}
