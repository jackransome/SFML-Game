#include "Image.h"
#include <iostream>

Image::Image() {}

Image::Image(sf::RenderWindow* pwindow, std::string _name, std::string path) {
	pWindow = pwindow;
	name = _name;
	sprite = sf::Sprite();
	texture = sf::Texture();
	texture.loadFromFile(path);
	sprite.setTexture(texture, true);	
}

void Image::draw(float x, float y) {
	sprite.setScale(1, 1);
	sprite.setPosition(x, y);
	sprite.setTexture(texture, true);
	executeDraw();
}

void Image::draw(float x, float y, float scale) {
	sprite.setPosition(x, y);
	sprite.setScale(scale, scale);
	sprite.setTexture(texture, true);
	executeDraw();
}

void Image::draw(float x, float y, float scale, float opacity) {
	sprite.setPosition(x, y);
	sprite.setScale(scale, scale);
	sprite.setColor(sf::Color(255, 255, 255, opacity * 255));
	sprite.setTexture(texture, true);
	executeDraw();
}

void Image::drawSection(float x, float y, int sX, int sY, int sW, int sH) {
	sprite.setTextureRect(sf::IntRect(sX, sY, sW, sH));
	sprite.setPosition(x, y);
	executeDraw();
}

void Image::drawSection(float x, float y, int sX, int sY, int sW, int sH, float scale) {
	sprite.setTextureRect(sf::IntRect(sX, sY, sW, sH));
	sprite.setPosition(x, y);
	sprite.setScale(scale, scale);
	executeDraw();
}

void Image::drawSection(float x, float y, int sX, int sY, int sW, int sH, float scale, float opacity) {
	sprite.setTextureRect(sf::IntRect(sX, sY, sW, sH));
	sprite.setPosition(x, y);
	sprite.setScale(scale, scale);
	sprite.setColor(sf::Color(255, 255, 255, opacity*255));
	executeDraw();
}

void Image::setShader(sf::Shader *_shader) {
	shader = _shader;
}

void Image::executeDraw() {
	if (shader == nullptr) {
		pWindow->draw(sprite);
	}
	else {
		pWindow->draw(sprite, shader);
	}
}


std::string Image::getName() {
	return name;
}
