#pragma once
#include "Graphics.h"
#include "InputManager.h"
#include "SpriteCollection.h"
#include "SoundPlayer.h"
#include "Camera.h"
#include "SpriteSheet.h"

class Game {
public:
	Game(sf::RenderWindow* pwindow);
	void HandleInput();
	void Run();
	void Draw();
private:
	float x = 500;
	float y = 500;
	bool lastSpace = false;
	Image *sprite1;
	Image* sprite2;
	Image* sprite3;
	Image* animation1;
	unsigned long frame = 0;
	glm::vec2 tranformedMousePos;
	sf::RenderWindow* pWindow;
	Graphics graphics;
	InputManager inputManager;
	SpriteCollection spriteCollection;
	SoundPlayer soundPlayer;
	Camera camera;
	SpriteSheet spriteSheet1;
};