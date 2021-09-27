#include "Game.h"

Game::Game(sf::RenderWindow* pwindow) {
	pWindow = pwindow;
	graphics = Graphics(pwindow);
	inputManager = InputManager(pwindow);
	spriteCollection = SpriteCollection(pwindow);
	soundPlayer = SoundPlayer();
	spriteCollection.createSprite("pic1", "resources/pic1.png");
	spriteCollection.createSprite("pic2", "resources/pic2.png");
	spriteCollection.createSprite("pic3", "resources/pic3.png");
	sprite1 = spriteCollection.getPointerFromName("pic1");
	sprite2 = spriteCollection.getPointerFromName("pic2");
	sprite3 = spriteCollection.getPointerFromName("pic3");
	soundPlayer.loadSound("hh", "resources/hh.wav");
	camera = Camera();
	camera.setScreenDimensions(1920, 1080);
	spriteCollection.setUseCamera(true);
	spriteCollection.setPCamera(&camera);
	spriteCollection.setOrderZ(true);
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
	camera.setPosition(glm::vec2(x, y));
	graphics.clearScreen(sf::Color(255, 255, 255, 100));
	//graphics.drawCircle(300, 300, 100, sf::Color(0, 255, 0, 255));
	//graphics.drawRect(600, 600, 30, 30, sf::Color(0, 0, 255, 255));

	spriteCollection.addSpriteDraw(sprite2, 400, 400, 400);
	spriteCollection.addSpriteDraw(sprite3, 800, 800, 800);
	spriteCollection.addSpriteDraw(sprite1, x, y, y);
	std::cout << y << "\n";
	spriteCollection.drawAll();

}
