#pragma once
#include <SFML/Graphics.hpp>

class Sprite {
public:
	Sprite();
	Sprite(sf::RenderWindow* pwindow, std::string name, std::string path);
	Sprite(sf::RenderWindow* pwindow, std::string name, std::string path, int width, int height, int frames);
	void run();
	void draw(float x, float y);
	std::string getName();
private:
	int frame = 0;
	int frames = 1;
	int width = 0;
	int height = 0;
	std::string name;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RenderWindow* pWindow;
};