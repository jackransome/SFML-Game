#pragma once
#include "Graphics.h"
#include "InputManager.h"
#include "SpriteCollection.h"
#include "SoundPlayer.h"

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
	Sprite* sprite;


	sf::RenderWindow* pWindow;
	Graphics graphics;
	InputManager inputManager;
	SpriteCollection spriteCollection;
	SoundPlayer soundPlayer;
};