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
	void setShader(sf::Shader *_shader);
	void executeDraw();
	std::string getName();
private:
	std::string name;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RenderWindow* pWindow;
	sf::Shader *shader;
};