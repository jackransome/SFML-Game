#pragma once
#include "Graphics.h"
#include "InputManager.h"
#include "SpriteCollection.h"
#include "SoundPlayer.h"
#include "Camera.h"

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
	Sprite *sprite1;
	Sprite *sprite2;
	Sprite* sprite3;
	Sprite *animation1;
	unsigned long frame = 0;
	glm::vec2 tranformedMousePos;

	sf::RenderWindow* pWindow;
	Graphics graphics;
	InputManager inputManager;
	SpriteCollection spriteCollection;
	SoundPlayer soundPlayer;
	Camera camera;
};