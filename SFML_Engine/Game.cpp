#include "Game.h"

Game::Game(sf::RenderWindow* pwindow) {
	pWindow = pwindow;
	graphics = Graphics(pwindow);
	inputManager = InputManager(pwindow);
	spriteCollection = SpriteCollection(pwindow, &graphics);
	soundPlayer = SoundPlayer();
	spriteCollection.createSprite("pic1", "resources/pic1.png");
	spriteCollection.createSprite("pic2", "resources/pic2.png");
	spriteCollection.createSprite("pic3", "resources/pic3.png");
	spriteCollection.createSprite("animation1", "resources/animation1.png", 144, 172, 4);
	sprite1 = spriteCollection.getPointerFromName("pic1");
	sprite2 = spriteCollection.getPointerFromName("pic2");
	sprite3 = spriteCollection.getPointerFromName("pic3");
	animation1 = spriteCollection.getPointerFromName("animation1");
	soundPlayer.loadSound("hh", "resources/hh.wav");
	camera = Camera();
	camera.setScreenDimensions(1920, 1080);
	camera.setScreenshakeCutoff(1);
	camera.setScreenshakeDecay(0.9);
	spriteCollection.setUseCamera(true);
	spriteCollection.setPCamera(&camera);
	spriteCollection.setOrderZ(true);
	spriteCollection.addFont("Taurus-Mono-Outline-Regular.ttf");
}

void Game::HandleInput() {
	inputManager.update();
	inputManager.translateMouseCoords(camera.getPosition().x, camera.getPosition().y);
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
			camera.addScreenshake(15);
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
	camera.runscreenShake();
	camera.setPosition(glm::vec2(x, y));
	graphics.clearScreen(sf::Color(255, 255, 255, 100));
	
	spriteCollection.addSpriteDraw(sprite2, 400, 400, 400);
	spriteCollection.addSpriteDraw(sprite3, 800, 800, 800);
	spriteCollection.addSpriteDraw(sprite1, 400, 800, 800);
	spriteCollection.addTextDraw(0, 20, 20, 20, "HELLO WORLD", 40, sf::Color::Black);


	spriteCollection.addAbsoluteCircleDraw(inputManager.mouseX, inputManager.mouseY, 50, inputManager.mouseY, sf::Color(255, 0, 0, 255));

	if (frame % 8 == 0) {
		animation1->run();
	}
	spriteCollection.addSpriteDraw(animation1, x, y, y);
	spriteCollection.drawAll();



	// inside the main loop, between window.clear() and window.display()

	frame++;
}
