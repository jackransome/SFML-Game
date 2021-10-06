#pragma once
#include <SFML/Graphics.hpp>

class Sprite {
public:
	Sprite();
	Sprite(sf::RenderWindow* pwindow, std::string name, std::string path, float scale);
	Sprite(sf::RenderWindow* pwindow, std::string name, std::string path, int width, int height, int frames, float scale);
	void run();
	void draw(float x, float y);
	void drawFrame(float x, float y, int frame);
	void setScale(float w, float h);
	std::string getName();
private:
	int frame = 0;
	int frames = 1;
	int width = 0;
	int height = 0;
	float scale;
	std::string name;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RenderWindow* pWindow;
};