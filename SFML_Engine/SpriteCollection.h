#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Graphics.h"
#include <iostream>
#include "SpriteDraw.h"

struct LightSource {
	LightSource() {}
	LightSource(glm::vec2 _position, glm::vec3 _colour, float _intensity) {
		position = _position;
		colour = _colour;
		intensity = _intensity;
	}
	glm::vec2 position;
	glm::vec3 colour;
	float intensity;
};

struct shaderWrapper {
	shaderWrapper(std::string _name, sf::Shader* _shader) {
		name = _name;
		shader = _shader;
	}
	std::string name;
	sf::Shader* shader;
};

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
	void addImageDraw(Image* pImage, float x, float y, float z, float scale, float opacity);
	void addImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale);
	void addImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float opacity);
	void addRotatedImageDraw(Image* pImage, float x, float y, float z, float scale, float rotation);
	void addRotatedImageDraw(Image* pImage, float x, float y, float z, float scale, float opacity, float rotation);
	void addRotatedImageDraw(Image* pImage, float x, float y, float z, float scale, float opacity, float rotation, float rx, float ry);
	void addRotatedImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float rotation);
	void addRotatedImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float rotation, float rx, float ry);
	void addRectDraw(float x, float y, float w, float h, float z, sf::Color);
	void addCircleDraw(float x, float y, float r, float z, sf::Color);
	void addAbsoluteImageDraw(Image* pImage, float x, float y, float z);
	void addAbsoluteImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH);
	void addAbsoluteImageDraw(Image* pImage, float x, float y, float z, float scale);
	void addAbsoluteImageDraw(Image* pImage, float x, float y, float z, float scale, float opacity);
	void addAbsoluteImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale);
	void addAbsoluteImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float opacity);
	void addAbsoluteRectDraw(float x, float y, float w, float h, float z, sf::Color);
	void addAbsoluteCircleDraw(float x, float y, float r, float z, sf::Color);
	void addTextDraw(int fontIndex, float x, float y, float z, std::string string, int fontSize, sf::Color color);
	void addAbsoluteTextDraw(int fontIndex, float x, float y, float z, std::string string, int _fontSize, sf::Color _color);
	void drawAll();
	void drawText(int fontIndex, float x, float y, std::string string, int _fontSize, sf::Color _color);
	void addFont(std::string name);
	void setShader(sf::Shader *shader);
	void addShader(std::string name, sf::Shader* shader);
	void drawLightSource(glm::vec2 position, glm::vec3 colour, float intensity, int type, bool absolute);
	void sendLightDataToShader();
	void setWindowDimensions(int w, int h);
	void addShaderToLast(std::string shader);
	void setFullBrightMode(bool _mode);
private:
	bool fullBrightMode = false;
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
	sf::Shader *lightingShader;
	LightSource lightsources[100];
	sf::Glsl::Vec2 lightPositions[100];
	sf::Glsl::Vec3 lightColours[100];
	float lightIntensities[100];
	float lightTypes[100];
	int windowW;
	int windowH;
	shaderWrapper* shaders[10];
	int nextShaderIndex = 0;
	int maxShaders = 10;
	int numLights = 0;
	bool lastAbsolute = false;;
};