#include "Game.h"

Game::Game(sf::RenderWindow* pwindow) {
	pWindow = pwindow;
	graphics = Graphics(pwindow);
	camera = Camera();
	inputManager = InputManager(pwindow);
	spriteCollection = SpriteCollection(pwindow, &graphics);
	soundPlayer = SoundPlayer();
	console = Console();
	timer = Timer(250, &console);
	objectCollection = ObjectCollection(&console, &inputManager, &spriteCollection, &soundPlayer, &camera);
	commandExecuter = CommandExecuter(&objectCollection, &soundPlayer, &camera, &spriteCollection, &inputManager);
	spriteCollection.loadImage("pic1", "resources/pic1.png");
	spriteCollection.loadImage("pic2", "resources/pic2.png");
	spriteCollection.loadImage("pic3", "resources/pic3.png");
	spriteCollection.loadImage("animation1", "resources/animation1.png");
	spriteCollection.loadImage("pillar_small_2", "resources/pillar_small_2.png");
	spriteCollection.loadImage("mc_walk_back", "resources/main_character/mc_walk_back.png");
	spriteCollection.loadImage("mc_walk_right", "resources/main_character/mc_walk_right.png");
	spriteCollection.loadImage("mc_walk_left", "resources/main_character/mc_walk_left.png");
	spriteCollection.loadImage("mc_walk_front", "resources/main_character/mc_walk_front.png");
	spriteCollection.loadImage("fire_animation_1", "resources/fire_animation_1.png");
	spriteCollection.loadImage("drone_fly", "resources/drone_fly.png");
	spriteCollection.loadImage("mc_run_left", "resources/main_character/mc_run_left.png");
	spriteCollection.loadImage("mc_run_right", "resources/main_character/mc_run_right.png");
	spriteCollection.loadImage("mc_blink_1", "resources/main_character/mc_blink_1.png");
	spriteCollection.loadImage("mc_stand_back", "resources/main_character/mc_stand_back.png");
	spriteCollection.loadImage("mc_stand_left", "resources/main_character/mc_stand_left.png");
	spriteCollection.loadImage("mc_stand_right", "resources/main_character/mc_stand_right.png");
	spriteCollection.loadImage("action1", "resources/action1.png");
	sprite1 = spriteCollection.getPointerFromName("pic1");
	sprite2 = spriteCollection.getPointerFromName("pic2");
	sprite3 = spriteCollection.getPointerFromName("pic3");
	//spriteSheet1 = SpriteSheet(pwindow, &spriteCollection, "animation1", 144, 172, 4, 1);
	//spriteSheet1 = SpriteSheet(pwindow, &spriteCollection, "animation2", 16, 26, 6, 2);
	//spriteSheet1.setDoesReset(false);
	soundPlayer.loadSound("hh", "resources/hh.wav");
	soundPlayer.loadSound("ohh", "resources/ohh.wav");
	soundPlayer.loadSound("sh", "resources/sh.wav");
	soundPlayer.loadSound("thk", "resources/thk2.wav");
	soundPlayer.loadSound("ex5", "resources/ex5.wav");
	soundPlayer.loadSound("1", "resources/1.wav");
	soundPlayer.loadSound("8tom", "resources/8tom.wav");
	soundPlayer.loadSound("hh2", "resources/hh2.wav");
	soundPlayer.loadSound("hh3", "resources/hh3.wav");
	soundPlayer.loadSound("beep1", "resources/beep1.wav");
	soundPlayer.loadSound("beep2", "resources/beep2.wav");
	soundPlayer.loadSound("hh4", "resources/hh4.wav");
	soundPlayer.loadSound("punch1", "resources/punch1.wav");
	screenW = 1920;
	screenH = 1080;
	camera.setScreenDimensions(screenW, screenH);
	camera.setScreenshakeCutoff(1);
	camera.setScreenshakeDecay(0.9);
	spriteCollection.setUseCamera(true);
	spriteCollection.setPCamera(&camera);
	spriteCollection.setOrderZ(true);
	spriteCollection.addFont("resources/fonts/Hacked_CRT.TTF");
	objectCollection.addMainCharacter(0, 0);
	objectCollection.addWall(300, 300, 100, 100);
	objectCollection.setDebug(false);
	objectCollection.addEnemy(200, 200);
	objectCollection.addEnemy(400, 200);
	objectCollection.addEnemy(300, 450);
}

void Game::HandleInput() {
	inputManager.update();
	if (inputManager.onKeyDown(space)) {
		console.addCommand(commandPlaySound, "hh");
		console.addCommand(commandShakeScreen, 15);	
	}
	if (inputManager.isKeyDown(f)) {
		console.addCommand(commandEnableDebug, 1);
	}
	if (inputManager.isKeyDown(g)) {
		console.addCommand(commandEnableDebug, 0);
	}
	if (inputManager.onKeyDown(e)) {
		console.addCommand(commandPlaySound, "thk");
		timer.addEvent(0, eventA, 0, 20, false);
	}
	if (inputManager.onKeyDown(r)) {
		console.addCommand(commandPlaySound, "thk");
		timer.addEvent(0, eventB, 0, 1, false);
	}
	/*if (inputManager.onKeyDown(t)) {
		console.addCommand(commandPlaySound, "thk");
		timer.addEvent(2, test3, 0, 1, true);
	}
	if (inputManager.onKeyDown(y)) {
		console.addCommand(commandPlaySound, "thk");
		timer.addEvent(1, test4, 0, 1, false);
	}
	if (inputManager.onKeyDown(u)) {
		console.addCommand(commandPlaySound, "thk");
		timer.addEvent(0, test1, 0, 1, false);
	}*/
}

void Game::Run() {
	objectCollection.update();
	objectCollection.runCollisionDetection();
	timer.update();
	while (console.getSize() > 0) {
		commandExecuter.execute(console.getCommand());
	}
	soundPlayer.update();
	inputManager.translateMouseCoords(camera.getPosition().x - screenW / 2, camera.getPosition().y - screenH / 2);
}

void Game::Draw() {

	// inside the main loop, between window.clear() and window.display()

	camera.runscreenShake();
	graphics.clearScreen(sf::Color(255, 255, 255, 100));

	spriteCollection.addImageDraw(sprite2, 400, 400, 400);
	spriteCollection.addImageDraw(sprite3, 800, 800, 800);
	spriteCollection.addImageDraw(sprite1, 400, 800, 800);
	spriteCollection.addTextDraw(0, 20, 20, 20, "Test Text hello world TEST", 40, sf::Color::Black);

	spriteCollection.addCircleDraw(inputManager.translatedMouseX - 15, inputManager.translatedMouseY - 15, 15, inputManager.mouseY, sf::Color(255, 0, 0, 255));
	

	spriteCollection.addRectDraw(200 + timer.getPhase() * 50, 200, 5, 20, 5, sf::Color(0, 0, 255, 255));

	objectCollection.draw();

	spriteCollection.drawAll();

	objectCollection.drawHealthBars();

	frame++;
}