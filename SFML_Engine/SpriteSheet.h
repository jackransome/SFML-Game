#pragma once
#include "SpriteCollection.h"

class SpriteSheet {
public:
	SpriteSheet();
	SpriteSheet(SpriteCollection* _pSpriteCollection, std::string name, int width, int height, int frames, float scale);
	void run();
	void draw(float x, float y, float z);
	void drawFrame(float x, float y, float z, int frame);
	std::string getName();
	void setDoesReset(bool _doesReset);
	void setChangeTimer(int _changeTimer);
	void reset();
	int getFrame();
private:
	int frame = 0;
	int frames = 1;
	int width = 0;
	int height = 0;
	float scale;
	bool doesReset = true;
	int changeTimer = 1;
	std::string name;
	sf::RenderWindow* pWindow;
	Image *pImage;
	SpriteCollection *pSpriteCollection;
	int timer = 0;
};