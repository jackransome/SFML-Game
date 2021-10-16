#pragma once
#include "Graphics.h"
#include "CommandExecuter.h"
#include "Console.h"

class Game {
public:
	Game(sf::RenderWindow* pwindow);
	void HandleInput();
	void Run();
	void Draw();
private:
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
	SpriteSheet spriteSheet2;
	SpriteSheet spriteSheet3;
	SpriteSheet spriteSheet4;
	SpriteSheet spriteSheet5;
	SpriteSheet spriteSheet6;
	SpriteSheet spriteSheet7;
	ObjectCollection objectCollection;
	Console console;
	CommandExecuter commandExecuter;
};