#pragma once
#include <SFML\Graphics.hpp>

class Graphics{
public:
	Graphics();
	Graphics(sf::RenderWindow *pwindow);
	void drawCircle(float x, float y, float radius, sf::Color color);
	void drawRect(float x, float y, float w, float h, sf::Color color);
	void clearScreen(sf::Color color);
	void setUseCamera(bool _useCamera);
private:
	sf::RenderWindow *pWindow;
	bool useCamera = false;
};