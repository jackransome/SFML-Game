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

void Image::addShader(sf::Shader *_shader) {
	if (nextShaderIndex >= maxShaders) {
		std::cout << "max number of shaders reached for this image\n";
		return;
	}
	shaders[nextShaderIndex] = _shader;
	nextShaderIndex++;
	numShaders++;
}

void Image::setFullBright() {
	fullBright = true;
}

void Image::executeDraw() {
	renderStates = sf::RenderStates::Default;// sf::RenderStates(sf::BlendNone, transform, NULL, shader);
	if (!fullBright) {
		renderStates.shader = shaders[0];
	}
	renderStates.transform = transform;


	//BS
	if (numShaders > 1) {
		sf::RenderTexture rt1;
		sf::RenderTexture rt2;
		sf::Sprite s1;
		sf::Sprite s2;
		rt1.create(1920, 1080);
		rt2.create(1920, 1080);
		//sf::RectangleShape rect(sf::Vector2f(40, 40));
		//rect.setPosition(200,200);
		//rect.setFillColor(sf::Color(0,255,0,255));
		//rt1.draw(rect);
		rt1.draw(sprite);
		rt1.display();
		s1 = sf::Sprite(rt1.getTexture());

		bool r2 = 1;
		for (int i = 0; i < numShaders-1; i++) {
			if (r2) {
				rt2.clear(sf::Color::Transparent);
				rt2.draw(s1, shaders[i]);
				rt2.display();
				s2 = sf::Sprite(rt2.getTexture());
			}
			else {
				rt1.clear(sf::Color::Transparent);
				rt1.draw(s2, shaders[i]);
				rt1.display();
				s1 = sf::Sprite(rt1.getTexture());
			}
			r2 = !r2;
		}

		if (r2) {
			pWindow->draw(s1, shaders[numShaders - 1]);
		}
		else {
			pWindow->draw(s2, shaders[numShaders - 1]);
		}
		numShaders = 0;
		nextShaderIndex = 0;
		return;
	}

	numShaders = 0;
	nextShaderIndex = 0;
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

void Image::finishWithoutDraw(){
	numShaders = 0;
	nextShaderIndex = 0;
}
