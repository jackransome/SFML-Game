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
// SETTING:
// snowing and empty, stone things rise out of the ground, activated by pressure pads and levers
// at some point you find an augmented reality headset, allowing you to access the main gameplay of the game (before this point sometimes you are randomly attacked / damaged
// some things follow you out of AR
// 
// 
// cinematic bits that show you fighting nothing
// sometimes the AR will flicker
// some effects in game will cause noisyness in AR, or cut it out
// 
// real enemies are revealed at somepoint, first appear in AR but remain when taking your headset off
// first AR encounter: put on, screen fased to black, then to black and white, then to colour with AR stuff
// 
// GOAL: explore, upgrade gear, learn more and escape
// 
// MUSIC:
// 
//		intro track will be track 1 from my ep
//		another track will be triasic period
//		use drone track for some death sounds and maybe ambience
//		untitled 149 from FL for happy victory or chill bustling area
//		tracks w breaks for in AR
// 
// MECHANICS:
// 
//  - GENERAL
//		AR things used to open up real world areas
//		hovering drone indicates when virtual enemies are nearby
//		mostfights will be in AR
//		puzzles will have some AR component most of the time
//		AR headset will have battery, when it runs out and enemies come you are defenseless
// 
//  - COMBAT:
//		you can dash twice and then have a cooldown
//		can place down pylons, or marks, when 2 have been place a beem appears between the two for a split second and damages all enemies inside (beam: fire? electric?)
//		Dying in AR = dying irl, like killed by the guardians in halo, maybe a stone pillar will rise out of the snow and laser beam you
//		
//	- hovering drone:
//		indicates when virtual enemies are nearby
//		also indicates nearby things you can interact with
//		may play a role in other puzzles, leaving you vulerable it you make it stay in one place for a task
//		may also become possessed in some parts of the story, going yellow?
//		
// 
//	- INTERRACTION AND INVENTORY
//		F to interract, must hold F to use things, fills up a box or bar, instead of just clicking
//		E to open inventory
//		Interacting with specific thing can open and close doors, as well as spawn enemies and structures
// 
//  - ENVIRONMENTS:
//		Outdoors: snow and footprints
//		Indoors: stone walls and floor
// 
// GRAPHICS:
//		Footprints and blood will be left on snow, fading away over time
// 
// TODO:
//		Global interfaces:
//			Graphics
//			Audio
//		Object class and inheritance and collection
//			bounding boxes
//			has z
//			generic drawing method
//			(for player, enemies, walls, stairs, items, Particle etc)
//			Object collection may need subsets that are loopable, for particles, enemies, etc
// 
//		Decoration class and inheritance and collection:
//			has xy and spritesheet/image
//			
//			(for blood, footsteps, burn marks)
// 
//		Particle class with inheritance and collection
//			Inherits object
//			has xyz and spritesheet/image
//			obeys same system as players and enemies in terms of elevated areas / cliffs
//			some should spawn decoration when landing / despawning
//			be able to remain on ground for set period of time, or disapear on impact
// 
//		Figure out system for elevated areas and stairs:
//			stairs: faster to walk down, slower to walk up
//			ledges/cliffs: falling off (moving off a raises platform(just a square) and not onto stairs, changes your position to a much greater y and adds equal z
//			then gravity and z is a thing
//
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