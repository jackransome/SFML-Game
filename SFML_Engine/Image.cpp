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
	if (rotationPoint) {
		transform = sf::Transform();
		transform.rotate(rotation, sf::Vector2f(x + rx, y + ry));
	}
	else {
		sprite.setRotation(rotation);
	}
	executeDraw();
}

void Image::draw(float x, float y, float scale) {
	sprite.setPosition(x, y);
	sprite.setScale(scale, scale);
	sprite.setTexture(texture, true);
	if (rotationPoint) {
		transform = sf::Transform();
		transform.rotate(rotation, sf::Vector2f(x + rx, y + ry));
	}
	else {
		sprite.setRotation(rotation);
	}
	executeDraw();
}

void Image::draw(float x, float y, float scale, float opacity) {
	if (name == "decoration_rover_tracks_1") {
		int r = 6;
	}
	sprite.setPosition(x, y);
	sprite.setScale(scale, scale);
	sprite.setColor(sf::Color(255, 255, 255, opacity * 255));
	sprite.setTexture(texture, true);
	if (rotationPoint) {
		transform = sf::Transform();
		transform.rotate(rotation, sf::Vector2f(x + rx, y + ry));
		//sprite.setRotation(rotation);
	}
	else {
		sprite.setRotation(rotation);
	}
	executeDraw();
}

void Image::drawSection(float x, float y, int sX, int sY, int sW, int sH) {
	sprite.setTextureRect(sf::IntRect(sX, sY, sW, sH));
	sprite.setPosition(x, y);
	transform = sf::Transform();
	if (rotationPoint) {
		transform.rotate(rotation, sf::Vector2f(x + rx, y + ry));
	}
	else {
		transform.rotate(rotation, sf::Vector2f(x + (sW * 1) / 2, y + (sH * 1) / 2));
	}
	executeDraw();
}

void Image::drawSection(float x, float y, int sX, int sY, int sW, int sH, float scale) {
	sprite.setTextureRect(sf::IntRect(sX, sY, sW, sH));
	sprite.setPosition(x, y);
	sprite.setScale(scale, scale);
	//sprite.setRotation(rotation);
	transform = sf::Transform();
	if (rotationPoint) {
		transform.rotate(rotation, sf::Vector2f(x + rx, y + ry));
	}
	else {
		transform.rotate(rotation, sf::Vector2f(x + (sW * scale) / 2, y + (sH * scale) / 2));
	}
	
	
	executeDraw();
}

void Image::drawSection(float x, float y, int sX, int sY, int sW, int sH, float scale, float opacity) {
	sprite.setTextureRect(sf::IntRect(sX, sY, sW, sH));
	sprite.setPosition(x, y);
	sprite.setScale(scale, scale);
	sprite.setColor(sf::Color(255, 255, 255, opacity*255));
	sprite.setRotation(rotation);
	executeDraw();
}

void Image::setShader(sf::Shader *_shader) {
	shader = _shader;
}

void Image::executeDraw() {
	renderStates = sf::RenderStates::Default;// sf::RenderStates(sf::BlendNone, transform, NULL, shader);
	renderStates.shader = shader;
	renderStates.transform = transform;
	pWindow->draw(sprite, renderStates);
}

void Image::setRotation(float _rotation){
	rotation = _rotation;
}

void Image::setRPoint(float _rx, float _ry){
	rotationPoint = true;
	rx = _rx;
	ry = _ry;
}


std::string Image::getName() {
	return name;
}
