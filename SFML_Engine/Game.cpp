#include "Game.h"

Game::Game(sf::RenderWindow* pwindow) {
	pWindow = pwindow;
	graphics = Graphics(pwindow);
	inputManager = InputManager(pwindow);
	spriteCollection = SpriteCollection(pwindow);
	soundPlayer = SoundPlayer();
	spriteCollection.createSprite("pic1", "resources/pic1.png");
	sprite = spriteCollection.getPointerFromName("pic1");
	soundPlayer.loadSound("hh", "resources/hh.wav");
}

void Game::HandleInput() {
	inputManager.update();
	if (inputManager.isKeyDown(w)) {
		y -= 5;
	}
	if (inputManager.isKeyDown(a)) {
		x -= 5;
	}
	if (inputManager.isKeyDown(s)) {
		y += 5;
	}
	if (inputManager.isKeyDown(d)) {
		x += 5;
	}
	if (inputManager.isKeyDown(space)) {
		if (!lastSpace) {
			soundPlayer.playSoundByName("hh");
		}		
		lastSpace = true;
	}
	else {
		lastSpace = false;
	}
}

void Game::Run() {

}

void Game::Draw() {
	graphics.clearScreen(sf::Color(50, 50, 50, 255));
	graphics.drawCircle(300, 300, 100, sf::Color(0, 255, 0, 255));
	graphics.drawRect(600, 600, 30, 30, sf::Color(0, 0, 255, 255));

	sprite->draw(x, y);

}
