#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Graphics.h"
#include <iostream>
#include "SpriteDraw.h"
#include "Shader_Pipeline_Classes.h"


class SpriteCollection {
public:
	SpriteCollection();
	SpriteCollection(sf::RenderWindow* pwindow, Graphics* pgraphics, MultiPipelineManager* _multiPipelineManager);
	void loadTexture(std::string name, std::string path);
	TextureWrapper* getPointerFromName(std::string name);
	void setUseCamera(bool _useCamera);
	void setPCamera(Camera *_pCamera);
	void setOrderZ(bool _orderZ);
	void addImageDraw(TextureWrapper* pTexture, float x, float y, float z, float w, float h);
	void addImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH);
	void addImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float _w, float _h);
	void addImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float opacity, float _w, float _h);
	void addImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale);
	void addImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float opacity);
	void addRotatedImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float rotation, float _w, float _h);
	void addRotatedImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float opacity, float rotation, float _w, float _h);
	void addRotatedImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float opacity, float rotation, float rx, float ry, float _w, float _h);
	void addRotatedImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float rotation);
	void addRotatedImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float rotation, float rx, float ry);
	void addRectDraw(float x, float y, float w, float h, float z, sf::Color);
	void addCircleDraw(float x, float y, float r, float z, sf::Color);
	void addAbsoluteImageDraw(TextureWrapper* pTexture, float x, float y, float z);
	void addAbsoluteImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH);
	void addAbsoluteImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale);
	void addAbsoluteImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float opacity);
	void addAbsoluteImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale);
	void addAbsoluteImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float opacity);
	void addAbsoluteRectDraw(float x, float y, float w, float h, float z, sf::Color);
	void addAbsoluteCircleDraw(float x, float y, float r, float z, sf::Color);
	void addTextDraw(int fontIndex, float x, float y, float z, std::string string, int fontSize, sf::Color color);
	void addAbsoluteTextDraw(int fontIndex, float x, float y, float z, std::string string, int _fontSize, sf::Color _color);
	void drawAll();
	void drawText(int fontIndex, float x, float y, std::string string, int _fontSize, sf::Color _color, sf::RenderTexture* target);
	void addFont(std::string name);
	void drawLightSource(glm::vec2 position, glm::vec3 colour, float intensity, int type);
	void drawBeamLight(glm::vec2 p1, glm::vec2 p2, glm::vec3 colour, float intensity, int type);
	void sendLightDataToShader();
	void setWindowDimensions(int* w, int* h);
	void setFullBrightMode(bool _mode);
	void blink();
	void setPipelineIndex(int index);
	void setLightShader(sf::Shader* shader);
	void setFrame(int _frame);
	sf::Texture rasterizeStack(int size, float w, float h);
	void drawRasterization(sf::Texture* texture, float z, float x, float y, float w, float h);
private:
	//settings
	bool bloomMode = false;
	bool fullBrightMode = false;

	//other
	int frame = 0;
	MultiPipelineManager* multiPipelineManager;
	int pipelineIndex = 0;
	bool toBlink = false;
	sf::RenderWindow *pWindow;
	Graphics *pGraphics;
	std::vector<TextureWrapper*> textureWrappers;
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
	int maxPointLights = 100;
	sf::Glsl::Vec2 pointLightPositions[100];
	sf::Glsl::Vec3 pointLightColours[100];
	float pointLightTypes[100];
	float pointLightIntensities[100];
	int numPointLights = 0;

	int maxBeamLights = 50;
	sf::Glsl::Vec2 beamLightPositions1[50];
	sf::Glsl::Vec2 beamLightPositions2[50];
	sf::Glsl::Vec3 beamLightColours[50];
	float beamLightTypes[50];
	float beamLightIntensities[50];
	int numBeamLights = 0;

	int* pWindowW;
	int* pWindowH;
	
	bool lastAbsolute = false;

	void clearSpriteDraws();
	void orderByZ();
};