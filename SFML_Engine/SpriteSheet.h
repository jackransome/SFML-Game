#pragma once
#include "SpriteCollection.h"

class SpriteSheet {
public:
	SpriteSheet();
	SpriteSheet(sf::RenderWindow* pwindow, SpriteCollection* _pSpriteCollection, std::string name, int width, int height, int frames, float scale);
	void run();
	void draw(float x, float y, float z);
	void drawFrame(float x, float y, float z, int frame);
	std::string getName();
private:
	int frame = 0;
	int frames = 1;
	int width = 0;
	int height = 0;
	float scale;
	std::string name;
	sf::RenderWindow* pWindow;
	Image *pImage;
	SpriteCollection *pSpriteCollection;
};