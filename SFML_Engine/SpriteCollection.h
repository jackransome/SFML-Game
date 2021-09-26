#pragma once
#include "Sprite.h"
#include <vector>

class SpriteCollection {
public:
	SpriteCollection();
	SpriteCollection(sf::RenderWindow* pwindow);
	void createSprite(std::string name, std::string path, int _width, int _height, int _frames);
	void createSprite(std::string name, std::string path);
	Sprite* getPointerFromName(std::string name);
private:
	sf::RenderWindow* pWindow;
	std::vector<Sprite*> sprites;
};