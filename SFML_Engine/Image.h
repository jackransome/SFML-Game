#pragma once
#include <SFML/Graphics.hpp>

class Image {
public:
	Image();
	Image(sf::RenderWindow* pwindow, std::string name, std::string path);
	void draw(float x, float y);
	void drawSection(float x, float y, int sX, int sY, int sW, int sH);
	void draw(float x, float y, float scale);
	void drawSection(float x, float y, int sX, int sY, int sW, int sH, float scale);
	std::string getName();
private:
	std::string name;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RenderWindow* pWindow;
};