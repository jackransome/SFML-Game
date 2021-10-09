#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Graphics.h"
#include <iostream>
#include "SpriteDraw.h"

class SpriteCollection {
public:
	SpriteCollection();
	SpriteCollection(sf::RenderWindow* pwindow, Graphics* pgraphics);
	void loadImage(std::string name, std::string path);
	Image* getPointerFromName(std::string name);
	void setUseCamera(bool _useCamera);
	void setPCamera(Camera *_pCamera);
	void setOrderZ(bool _orderZ);
	void addImageDraw(Image* pImage, float x, float y, float z);
	void addImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH);
	void addImageDraw(Image* pImage, float x, float y, float z, float scale);
	void addImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale);
	void addRectDraw(float x, float y, float w, float h, float z, sf::Color);
	void addCircleDraw(float x, float y, float r, float z, sf::Color);
	void addAbsoluteImageDraw(Image* pImage, float x, float y, float z);
	void addAbsoluteImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH);
	void addAbsoluteImageDraw(Image* pImage, float x, float y, float z, float scale);
	void addAbsoluteImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale);
	void addAbsoluteRectDraw(float x, float y, float w, float h, float z, sf::Color);
	void addAbsoluteCircleDraw(float x, float y, float r, float z, sf::Color);
	void addTextDraw(int fontIndex, float x, float y, float z, std::string string, int fontSize, sf::Color color);
	void addAbsoluteTextDraw(int fontIndex, float x, float y, float z, std::string string, int _fontSize, sf::Color _color);
	void drawAll();
	void drawText(int fontIndex, float x, float y, std::string string, int _fontSize, sf::Color _color);
	void addFont(std::string name);
private:
	void clearSpriteDraws();
	void orderByZ();
	sf::RenderWindow *pWindow;
	Graphics *pGraphics;
	std::vector<Image*> images;
	int maxSpriteDraws = 1000;
	int maxAbsoluteSpriteDraws = 1000;
	SpriteDraw *spriteDraws[1000];
	SpriteDraw *absoluteSpriteDraws[1000];
	int currentDrawIndex = 0;
	int currentAbsoluteDrawIndex = 0;
	bool useCamera = false;
	Camera *pCamera;
	std::vector<sf::Font> fonts;
	bool orderZ = false;
};