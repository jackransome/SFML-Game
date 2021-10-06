#include "Game.h"

Game::Game(sf::RenderWindow* pwindow) {
	pWindow = pwindow;
	graphics = Graphics(pwindow);
	inputManager = InputManager(pwindow);
	spriteCollection = SpriteCollection(pwindow, &graphics);
	soundPlayer = SoundPlayer();
	spriteCollection.loadImage("pic1", "resources/pic1.png");
	spriteCollection.loadImage("pic2", "resources/pic2.png");
	spriteCollection.loadImage("pic3", "resources/pic3.png");
	spriteCollection.loadImage("animation1", "resources/animation1.png");
	spriteCollection.loadImage("animation2", "resources/pillar_small_2.png");
	sprite1 = spriteCollection.getPointerFromName("pic1");
	sprite2 = spriteCollection.getPointerFromName("pic2");
	sprite3 = spriteCollection.getPointerFromName("pic3");
	//spriteSheet1 = SpriteSheet(pwindow, &spriteCollection, "animation1", 144, 172, 4, 1);
	spriteSheet1 = SpriteSheet(pwindow, &spriteCollection, "animation2", 16, 26, 6, 2);
	spriteSheet1.setChangeTimer(8);
	spriteSheet1.setDoesReset(false);
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

// GAME plan
//
// snowing and empty, stone things rise out of the ground, activated by pressure pads and levers
// are gives you an augmented reality headset, allowing you to access the main gameplay of the game
// some things follow you out of AR
// AR things used to open up real world areas
// Dying in AR = dying irl, like killed by the guardians in halo, maybe a stone pillar will rise out of the snow and laser beam you
// cinematic bits that show you fighting nothing
// sometimes the AR will flicker
// some effects in game will cause noisyness in AR, or cut it out
// hovering drone indicates when virtual enemies are nearby
// real enemies are revealed at somepoint, first appear in AR but remain when taking your headset off
// 
// GOAL: explore, upgrade gear, learn more and escape
// 
// MUSIC:
// 
// intro track will be track 1 from my ep
// another track will be triasic period
// use drone track for some death sounds and maybe ambience
// untitled 149 from FL for happy victory or chill bustling area
// 



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
	if (inputManager.mouseL) {
		spriteSheet1.reset();
	}
}

void Game::Run() {

}

void Game::Draw() {

	// inside the main loop, between window.clear() and window.display()

	camera.runscreenShake();
	camera.setPosition(glm::vec2(x, y));
	graphics.clearScreen(sf::Color(255, 255, 255, 100));

	spriteCollection.addImageDraw(sprite2, 400, 400, 400);
	spriteCollection.addImageDraw(sprite3, 800, 800, 800);
	spriteCollection.addImageDraw(sprite1, 400, 800, 800);
	spriteCollection.addTextDraw(0, 20, 20, 20, "HELLO WORLD", 40, sf::Color::Black);


	spriteCollection.addAbsoluteCircleDraw(inputManager.mouseX, inputManager.mouseY, 50, inputManager.mouseY, sf::Color(255, 0, 0, 255));

	spriteSheet1.run();
	spriteSheet1.draw(x, y, y);

	spriteCollection.drawAll();

	

	frame++;
}