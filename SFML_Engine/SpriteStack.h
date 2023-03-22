#pragma once
#include "SpriteCollection.h"

class SpriteStack {
public:
	SpriteStack();
	SpriteStack(SpriteCollection* _pSpriteCollection, std::string _name, int width, int height, int frames, float scale);
	void draw(float x, float y, float z, float rotation);
	void draw(float x, float y, float z, float rotation, float rx, float ry);
	void draw(float x, float y, float z, float rotation, std::string shader);
	void draw(float x, float y, float z, float rotation, float rx, float ry, std::string shader);
	void setOpacity(float _opacity);
private:
	int frames = 1;
	int width = 0;
	int height = 0;
	float scale;
	TextureWrapper* pTexture;
	SpriteCollection* pSpriteCollection;
	float opacity = 1;
};