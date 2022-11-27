#pragma once
#include <SFML/Graphics.hpp>

class Image {
public:
	Image();
	Image(sf::RenderWindow* pwindow, std::string name, std::string path);
	void draw(float x, float y);
	void drawSection(float x, float y, int sX, int sY, int sW, int sH);
	void draw(float x, float y, float scale);
	void draw(float x, float y, float scale, float opacity);
	void drawSection(float x, float y, int sX, int sY, int sW, int sH, float scale);
	void drawSection(float x, float y, int sX, int sY, int sW, int sH, float scale, float opacity);
	void addShader(sf::Shader *_shader);
	void setFullBright();
	void executeDraw();
	void setRotation(float _rotation);
	void setRPoint(float _rx, float _ry);
	std::string getName();
private:
	bool fullBright = false;;
	int rotationPointx = 0;
	int rotationPointy = 0;
	int height;
	float rotation = 0;
	bool rotationPoint = false;
	float rx;
	float ry;
	std::string name;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RenderWindow* pWindow;
	sf::Shader *shaders[10];
	const int maxShaders = 10;
	int nextShaderIndex = 0;
	int numShaders;
	sf::Transform transform;
	sf::RenderStates renderStates;
};