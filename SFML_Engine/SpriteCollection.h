#pragma once
#include "Sprite.h"
#include <vector>
#include <glm/glm.hpp>
#include "Camera.h"

struct SpriteDraw {
	SpriteDraw() {}
	SpriteDraw(Sprite* _pSprite, float _x, float _y, float _z) {
		pSprite = _pSprite;
		x = _x;
		y = _y;
		z = _z;
	}
	Sprite* pSprite;
	float x;
	float y;
	float z;
};

class SpriteCollection {
public:
	SpriteCollection();
	SpriteCollection(sf::RenderWindow* pwindow);
	void createSprite(std::string name, std::string path, int _width, int _height, int _frames);
	void createSprite(std::string name, std::string path);
	Sprite* getPointerFromName(std::string name);
	void setUseCamera(bool _useCamera);
	void setPCamera(Camera *_pCamera);
	void setOrderZ(bool _orderZ);
	void addSpriteDraw(Sprite* pSprite, float x, float y, float z);
	void drawAll();
private:
	void clearSpriteDraws();
	void orderByZ();
	sf::RenderWindow *pWindow;
	std::vector<Sprite*> sprites;
	int maxSpriteDraws = 1000;
	SpriteDraw *spriteDraws;
	int currentDrawIndex = 0;
	bool useCamera = false;
	Camera *pCamera;
	bool orderZ = false;
};