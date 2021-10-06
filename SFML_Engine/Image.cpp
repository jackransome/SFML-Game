#include "Image.h"

Image::Image() {}

Image::Image(sf::RenderWindow* pwindow, std::string _name, std::string path) {
	pWindow = pwindow;
	name = _name;
	sprite = sf::Sprite();
	texture = sf::Texture();
	texture.loadFromFile(path);
	sprite.setTexture(texture);
}

void Image::draw(float x, float y) {
	sprite.setScale(1, 1);
	sprite.setPosition(x, y);
	pWindow->draw(sprite);
}

void Image::draw(float x, float y, float scale) {
	sprite.setPosition(x, y);
	sprite.setScale(scale, scale);
	pWindow->draw(sprite);
}

void Image::drawSection(float x, float y, int sX, int sY, int sW, int sH) {
	sprite.setTextureRect(sf::IntRect(sX, sY, sW, sH));
	sprite.setPosition(x, y);
	pWindow->draw(sprite);
}

void Image::drawSection(float x, float y, int sX, int sY, int sW, int sH, float scale) {
	sprite.setTextureRect(sf::IntRect(sX, sY, sW, sH));
	sprite.setPosition(x, y);
	sprite.setScale(scale, scale);
	pWindow->draw(sprite);
}


std::string Image::getName() {
	return name;
}
