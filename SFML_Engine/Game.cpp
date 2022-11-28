#include "Game.h"

Game::Game(sf::RenderWindow* pwindow) {
	screenW = 1920;
	screenH = 1080;
	pWindow = pwindow;
	graphics = Graphics(pwindow);
	camera = Camera();
	inputManager = InputManager(pwindow);
	
	shader1.loadFromFile("shaders/shader1.frag", sf::Shader::Fragment);
	shader1.setUniform("texture", sf::Shader::CurrentTexture);
	spriteCollection = SpriteCollection(pwindow, &graphics);
	spriteCollection.addShader("shader1",  &shader1);
	shaders[0] = new sf::Shader();
	shaders[0]->loadFromFile("shaders/test.frag", sf::Shader::Fragment);
	spriteCollection.addShader("test", shaders[0]);
	shaders[1] = new sf::Shader();
	shaders[1]->loadFromFile("shaders/test2.frag", sf::Shader::Fragment);
	spriteCollection.addShader("test2", shaders[1]);
	shaders[2] = new sf::Shader();
	shaders[2]->loadFromFile("shaders/blur_h.frag", sf::Shader::Fragment);
	spriteCollection.addShader("blur_h", shaders[2]);
	shaders[3] = new sf::Shader();
	shaders[3]->loadFromFile("shaders/blur_v.frag", sf::Shader::Fragment);
	spriteCollection.addShader("blur_v", shaders[3]);
	shaders[4] = new sf::Shader();
	shaders[4]->loadFromFile("shaders/blend.frag", sf::Shader::Fragment);
	spriteCollection.addShader("blend", shaders[4]);
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
	spriteCollection.loadImage("mc_run_down", "resources/main_character/mc_run_down2.png");
	spriteCollection.loadImage("mc_run_up", "resources/main_character/mc_run_up.png");
	spriteCollection.loadImage("mc_blink_1", "resources/main_character/mc_blink_1.png");
	spriteCollection.loadImage("mc_stand_back", "resources/main_character/mc_stand_back.png");
	spriteCollection.loadImage("mc_stand_left", "resources/main_character/mc_stand_left.png");
	spriteCollection.loadImage("mc_stand_right", "resources/main_character/mc_stand_right.png");
	spriteCollection.loadImage("action1", "resources/action1.png");
	spriteCollection.loadImage("mc_mini_run_right", "resources/main_character/mc_mini_run_right.png"); 
	spriteCollection.loadImage("enemyDrone1", "resources/enemyDrone1.png");
	spriteCollection.loadImage("snow1", "resources/snow2.png");
	spriteCollection.loadImage("white_background", "resources/white_background.png");
	spriteCollection.loadImage("XFrame", "resources/XFrame.png");
	spriteCollection.loadImage("wall_texture1", "resources/wall_texture1.png");
	spriteCollection.loadImage("platform_top_edge", "resources/platform_top_edge.png");
	spriteCollection.loadImage("platform_top_main", "resources/platform_top_main.png");
	spriteCollection.loadImage("rover_stack_1", "resources/rover_stack_1.png"); 
	spriteCollection.loadImage("rover_stack_crate", "resources/rover_stack_crate.png");
	spriteCollection.loadImage("crate_stack_1", "resources/crate_stack_1.png");
	spriteCollection.loadImage("decoration_rover_tracks_1", "resources/decoration_rover_tracks_1.png");
	spriteCollection.loadImage("relay_stack_1", "resources/relay_stack_1.png");
	spriteCollection.loadImage("rover_stack_relay", "resources/rover_stack_relay.png");
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
	soundPlayer.loadSound("wind", "resources/wind_better2.wav");
	soundPlayer.loadSound("footstep_snow", "resources/footstep_snow.wav");
	soundPlayer.loadSound("rover_move_1", "resources/sound_rover_move_1.wav");
	soundPlayer.loadSound("pickup", "resources/sound_pickup.wav");
	soundPlayer.loadSound("drop", "resources/sound_drop.wav");
	snowSystem = SnowSystem(&spriteCollection, screenW, screenH, camera.getPosition());
	camera.setScreenDimensions(screenW, screenH);
	camera.setScreenshakeCutoff(0.1);
	camera.setScreenshakeDecay(0.9);
	spriteCollection.setUseCamera(true);
	spriteCollection.setPCamera(&camera);
	spriteCollection.setOrderZ(true);
	spriteCollection.addFont("resources/fonts/Hacked_CRT.TTF");
	objectCollection.addMainCharacter(0, 0);
	objectCollection.addWall(300, 300, 100, 100);
	objectCollection.addWall(500, 300, 100, 100);
	objectCollection.addWall(300, -100, 100, 100);
	objectCollection.setDebug(false);
	objectCollection.addEnemy(200, 200);
	objectCollection.addRover(-100, -100);
	objectCollection.addRelay(-200, -500);
	//objectCollection.addEnemy(400, 200);
	//objectCollection.addEnemy(300, 450);
	spriteCollection.setWindowDimensions(screenW, screenH);
	ambientLightColour = sf::Glsl::Vec3(255/255.0, 253/255.0, 240/255.0);
	//console.addCommand(commandPlaySound, "wind");
	int id = soundPlayer.playSoundByName("wind", 0.25);
	soundPlayer.loopSound(id);
	//blizzard conditions
	snowSystem.setSpeed(5);
	snowSystem.setFallAngle(0.5);
	snowSystem.setSize(20);
	snowOpacity = 0.25;
	snowSystem.setOpacity(snowOpacity);
	console.addCommand(commandSetCameraFocusId, 0);
	console.addCommand(commandEnableObjectControls, 0);
	objectCollection.addCrate(-30, 30);

}

void Game::HandleInput() {
	inputManager.update();
	if (inputManager.onKeyDown(space)) {
		console.addCommand(commandPlaySound, "hh");
		console.addCommand(commandShakeScreen, 15.0f);	
	}
	if (inputManager.isKeyDown(f)) {
		console.addCommand(commandEnableDebug, 1);
	}
	if (inputManager.isKeyDown(g)) {
		console.addCommand(commandEnableDebug, 0);
	}
	if (inputManager.isKeyDown(r)) {
		if (snowOpacity <= 0.99) {
			snowOpacity += 0.01;
			snowSystem.setOpacity(snowOpacity);
		}
	}
	if (inputManager.isKeyDown(t)) {
		if (snowOpacity >= 0.01) {
			snowOpacity -= 0.01;
			snowSystem.setOpacity(snowOpacity);
		}
	}
	if (inputManager.isKeyDown(y)) {
		snowSystem.setSpeed(10);
		snowSystem.setFallAngle(0.5);
		snowSystem.setSize(50);
	}
	if (inputManager.isKeyDown(u)) {
		snowSystem.setSpeed(1);
		snowSystem.setFallAngle(1.6);
		snowSystem.setSize(30);
	}

	if (inputManager.isKeyDown(upArrow)) {
		if (daylightPhase <= 0.99) {
			daylightPhase += 0.01;
		}
		if (ambientLightLevel <= 0.99) {
			ambientLightLevel += 0.01;
		}
	}
	if (inputManager.isKeyDown(downArrow)) {
		if (ambientLightLevel >= 0.01) {
			ambientLightLevel -= 0.01;
		}
		if (daylightPhase >= 0.01) {
			daylightPhase -= 0.01;
		}
	}
	if (inputManager.isKeyDown(n0)) {
		console.addCommand(commandSetCameraFocusId, 0);
		console.addCommand(commandEnableObjectControls, 0);
	}
	if (inputManager.isKeyDown(n1)) {
		console.addCommand(commandSetCameraFocusId, 0);
		console.addCommand(commandEnableObjectControls, 0);
	}
	if (inputManager.isKeyDown(n2)) {
		console.addCommand(commandSetCameraFocusId, 5);
		console.addCommand(commandEnableObjectControls, 5);
	}
	if (inputManager.isKeyDown(n3)) {
		console.addCommand(commandSetCameraFocusId, 4);
		console.addCommand(commandEnableObjectControls, 4);
	}
	if (inputManager.isKeyDown(n4)) {
		console.addCommand(commandSetCameraFocusId, 4);
		console.addCommand(commandEnableObjectControls, 4);
	}
	if (inputManager.isKeyDown(n5)) {
		console.addCommand(commandSetCameraFocusId, 5);
		console.addCommand(commandEnableObjectControls, 5);
	}
	if (inputManager.isKeyDown(n6)) {
		console.addCommand(commandSetCameraFocusId, 6);
		console.addCommand(commandEnableObjectControls, 6);
	}
	


	shader1.setUniform("ambientLightLevel", ambientLightLevel);
	shader1.setUniform("ambientLightColour", ambientLightColour);
	shader1.setUniform("time", (float)(frame % 30)); 
	shader1.setUniform("noiseIntensity", shaderNoiseIntensity);
	//if (inputManager.onKeyDown(e)) {
	//	console.addCommand(commandPlaySound, "thk");
	//	timer.addEvent(0, eventA, 0, 20, false);
	//}
	//if (inputManager.onKeyDown(r)) {
	//	console.addCommand(commandPlaySound, "thk");
	//	timer.addEvent(0, eventB, 0, 1, false);
	//}
	/*if (inputManager.onKeyDown(t)) {
		console.addCommand(commandPlaySound, "thk");
		timer.addEvent(2, test3, 0, 1, true);
	}
	if (inputManager.onKeyDown(y)) {s
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
	objectCollection.setEnemyTarget(inputManager.translatedMouseX, inputManager.translatedMouseY);
	//timer.update();
	while (console.getSize() > 0) {
		commandExecuter.execute(console.getCommand());
	}
	soundPlayer.update();
	inputManager.translateMouseCoords(camera.getPosition().x - screenW / 2, camera.getPosition().y - screenH / 2);
	snowSystem.run(camera.getPosition());
	console.incrementFrame();
	if (daylightPhase < 0.5) {
		ambientLightColour = sf::Glsl::Vec3(255, 112 + 128 * daylightPhase*2, 69 + 121 * daylightPhase*2);
	}
	else {
		ambientLightColour = sf::Glsl::Vec3(255 - 33 * (daylightPhase-0.5)*2, 240 - 2 * (daylightPhase - 0.5) * 2, 190 + 65 * (daylightPhase - 0.5) * 2);
	}
	
}

void Game::Draw() {
	spriteCollection.drawLightSource(glm::vec2(0, 200), glm::vec3(255, 255, 255), 0.75, 0, false);
	// inside the main loop, between window.clear() and window.display()

	camera.runscreenShake();
	
	//spriteCollection.addRectDraw(camera.getPosition().x - 1920 / 2, camera.getPosition().y - 1080 / 2, 1920, 1080, -10000, sf::Color::White);
	//spriteCollection.addImageDraw(sprite2, 400, 400, 400);
	//spriteCollection.addImageDraw(sprite3, 800, 800, 800);
	
	//spriteCollection.addImageDraw(sprite1, 400, 800, 800);
	pWindow->clear();

	spriteCollection.addImageDraw(spriteCollection.getPointerFromName("white_background"), camera.getPosition().x - 1920 / 2, camera.getPosition().y - 1080 / 2, -100000, 1, 1);
	
	spriteCollection.addTextDraw(0, 20, 20, 20, "Test Text hello world TEST", 40, sf::Color::Black);

	spriteCollection.addImageDraw(spriteCollection.getPointerFromName("XFrame"), 300, 300, 300+88*4, 4, 1);
	spriteCollection.addImageDraw(spriteCollection.getPointerFromName("XFrame"), -300, 300, 300 + 88 * 4, 4, 1);
	spriteCollection.addImageDraw(spriteCollection.getPointerFromName("XFrame"), -300, -300, -300 + 88 * 4, 4, 1);


	//spriteCollection.addCircleDraw(inputManager.translatedMouseX - 15, inputManager.translatedMouseY - 15, 15, inputManager.mouseY, sf::Color(255, 0, 0, 255));
	
	//spriteCollection.addRectDraw(200 + timer.getPhase() * 50, 200, 5, 20, 5, sf::Color(0, 0, 255, 255));

	objectCollection.draw();

	snowSystem.draw();

	

	//objectCollection.drawHealthBars();

	spriteCollection.drawAll();

	

	frame++;
}

void Game::finishAudio(){
	soundPlayer.finish();
}
