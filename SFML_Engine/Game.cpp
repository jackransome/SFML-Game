#include "Game.h"

Game::Game(sf::RenderWindow* pwindow) : physicsWorld(b2Vec2(0, 0)) {
	screenW = 1920;
	screenH = 1080;
	pWindow = pwindow;
	graphics = Graphics(pwindow);
	camera = Camera();
	inputManager = InputManager(pwindow, &screenW, &screenH);

	auto defaultPipeline = std::make_shared<RenderingPipeline>(false);
	auto pipelineL = std::make_shared<RenderingPipeline>(false);
	auto pipelineN = std::make_shared<RenderingPipeline>(false);

	shaderManager = ShaderManager();

	// Loading shaders with ShaderManager
	shaderManager.loadShader("brightness_threshold", "shaders/brightness_threshold.frag", sf::Shader::Fragment);
	shaderManager.loadShader("lighting", "shaders/shader1.frag", sf::Shader::Fragment);
	shaderManager.loadShader("test", "shaders/test.frag", sf::Shader::Fragment);
	shaderManager.loadShader("test2", "shaders/test2.frag", sf::Shader::Fragment);
	shaderManager.loadShader("blur_h", "shaders/blur_h.frag", sf::Shader::Fragment);
	shaderManager.loadShader("blur_v", "shaders/blur_v.frag", sf::Shader::Fragment);
	shaderManager.loadShader("blend", "shaders/blend.frag", sf::Shader::Fragment);
	shaderManager.loadShader("colour", "shaders/colour.frag", sf::Shader::Fragment);
	shaderManager.loadShader("bloom", "shaders/bloom.frag", sf::Shader::Fragment);
	shaderManager.loadShader("bloom_v", "shaders/bloom_v.frag", sf::Shader::Fragment);
	shaderManager.loadShader("default", "shaders/default.frag", sf::Shader::Fragment);

	defaultPipeline->addStage(shaderManager.getShader("default"));

	pipelineL->addStage(shaderManager.getShader("lighting"));
	
	pipelineN->addStage(shaderManager.getShader("lighting"));
	pipelineN->addStage(shaderManager.getShader("brightness_threshold"));
	pipelineN->addStage(shaderManager.getShader("bloom"));
	pipelineN->addStage(shaderManager.getShader("bloom_v"));
	
	auto defaultMultiPipeline = std::make_shared<MultiPipeline>();
	defaultMultiPipeline->addPipeline(defaultPipeline);
	
	auto multiPipelineL = std::make_shared<MultiPipeline>();
	multiPipelineL->addPipeline(pipelineL);

	auto multiPipelineN = std::make_shared<MultiPipeline>();
	multiPipelineN->addPipeline(pipelineN);

	multiPipelineManager = MultiPipelineManager();
	multiPipelineManager.addMultiPipeline(defaultMultiPipeline);
	multiPipelineManager.addMultiPipeline(multiPipelineL);
	multiPipelineManager.addMultiPipeline(multiPipelineN);
	

	spriteCollection = SpriteCollection(pWindow, &graphics, &multiPipelineManager);
	spriteCollection.setPipelineIndex(0);

	spriteCollection.setLightShader(shaderManager.getShader("lighting"));

	soundPlayer = SoundPlayer();
	soundPlayer.setGlobalVolume(1);
	console = Console();
	timer = Timer(250, &console);
	objectCollection = ObjectCollection(&console, &inputManager, &spriteCollection, &soundPlayer, &camera, &physicsWorld);
	commandExecuter = CommandExecuter(&objectCollection, &soundPlayer, &camera, &spriteCollection, &inputManager);
	controlSwitcher = ControlSwitcher(&objectCollection, &console, &spriteCollection);
	
	spriteCollection.loadTexture("pic1", "resources/pic1.png");
	spriteCollection.loadTexture("pic2", "resources/pic2.png");
	spriteCollection.loadTexture("pic3", "resources/pic3.png");
	spriteCollection.loadTexture("animation1", "resources/animation1.png");
	spriteCollection.loadTexture("pillar_small_2", "resources/pillar_small_2.png");
	spriteCollection.loadTexture("mc_walk_back", "resources/main_character/mc_walk_back.png");
	spriteCollection.loadTexture("mc_walk_right", "resources/main_character/mc_walk_right.png");
	spriteCollection.loadTexture("mc_walk_left", "resources/main_character/mc_walk_left.png");
	spriteCollection.loadTexture("mc_walk_front", "resources/main_character/mc_walk_front.png");
	spriteCollection.loadTexture("fire_animation_1", "resources/fire_animation_1.png");
	spriteCollection.loadTexture("drone_fly", "resources/drone_fly.png");
	spriteCollection.loadTexture("mc_run_left", "resources/main_character/mc_run_left.png");
	spriteCollection.loadTexture("mc_run_right", "resources/main_character/mc_run_right.png");
	spriteCollection.loadTexture("mc_run_down", "resources/main_character/mc_run_down2.png");
	spriteCollection.loadTexture("mc_run_up", "resources/main_character/mc_run_up.png");
	spriteCollection.loadTexture("mc_blink_1", "resources/main_character/mc_blink_1.png");
	spriteCollection.loadTexture("mc_stand_back", "resources/main_character/mc_stand_back.png");
	spriteCollection.loadTexture("mc_stand_left", "resources/main_character/mc_stand_left.png");
	spriteCollection.loadTexture("mc_stand_right", "resources/main_character/mc_stand_right.png");
	spriteCollection.loadTexture("action1", "resources/action1.png");
	spriteCollection.loadTexture("mc_mini_run_right", "resources/main_character/mc_mini_run_right.png"); 
	spriteCollection.loadTexture("enemyDrone1", "resources/enemyDrone1.png");
	spriteCollection.loadTexture("snow1", "resources/snow2.png");
	spriteCollection.loadTexture("white_background", "resources/white_background.png");
	spriteCollection.loadTexture("XFrame", "resources/XFrame.png");
	spriteCollection.loadTexture("wall_texture1", "resources/wall_texture1.png");
	spriteCollection.loadTexture("platform_top_edge", "resources/platform_top_edge.png");
	spriteCollection.loadTexture("platform_top_main", "resources/platform_top_main.png");
	spriteCollection.loadTexture("rover_stack_1", "resources/rover_stack_1.png"); 
	spriteCollection.loadTexture("rover_stack_crate", "resources/rover_stack_crate.png");
	spriteCollection.loadTexture("crate_stack_1", "resources/crate_stack_1.png");
	spriteCollection.loadTexture("decoration_rover_tracks_1", "resources/decoration_rover_tracks_1.png");
	spriteCollection.loadTexture("relay_stack_1", "resources/relay_stack_1.png");
	spriteCollection.loadTexture("rover_stack_relay", "resources/rover_stack_relay.png");
	spriteCollection.loadTexture("scrap_stack_1", "resources/scrap_stack_1.png"); 
	spriteCollection.loadTexture("scrap_drop_stack_1", "resources/scrap_drop_stack_2.png");
	spriteCollection.loadTexture("market_relay", "resources/market_relay.png");
	spriteCollection.loadTexture("autoturret_base_stack", "resources/autoturret_base_stack.png");
	spriteCollection.loadTexture("autoturret_barrel_stack", "resources/autoturret_barrel_stack.png");
	spriteCollection.loadTexture("white_rect", "resources/white_rect.png");
	spriteCollection.loadTexture("menu_bg", "resources/menu_bg.png");
	spriteCollection.loadTexture("menu_mc", "resources/menu_mc_p.png");
	spriteCollection.loadTexture("menu_eyes", "resources/menu_eyes_p.png");
	spriteCollection.loadTexture("menu_snow", "resources/menu_snow.png");
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
	soundPlayer.loadSound("rover_mine_1", "resources/sound_rover_mine_1.wav");
	soundPlayer.loadSound("pickup", "resources/sound_pickup.wav");
	soundPlayer.loadSound("drop", "resources/sound_drop.wav");
	soundPlayer.loadSound("mine_hit_1", "resources/sound_mine_hit_1.wav");
	soundPlayer.loadSound("transfer", "resources/sound_transfer.wav");
	soundPlayer.loadSound("laser_shot", "resources/sound_laser_shot.wav");
	soundPlayer.loadSound("drone_death_2", "resources/sound_drone_death_2.wav");
	soundPlayer.loadSound("drone_zap_1", "resources/sound_drone_zap_1.wav");
	soundPlayer.loadSound("drone_zap_2", "resources/sound_drone_zap_2.wav");
	soundPlayer.loadSound("drone_zap_3", "resources/sound_drone_zap_3.wav");
	soundPlayer.loadSound("drone_zap_4", "resources/sound_drone_zap_4.wav");
	soundPlayer.loadSound("drone_zap_5", "resources/sound_drone_zap_5.wav");
	soundPlayer.loadSound("relay_ambient_2", "resources/sound_relay_ambient_2.wav"); 
	soundPlayer.loadSound("drone_ambient_1", "resources/sound_drone_ambient_2.wav");
	soundPlayer.loadSound("relay_ambient_3", "resources/sound_relay_ambient_3.wav");
	soundPlayer.loadSound("drone_hit_1", "resources/sound_drone_hit_1.wav");
	soundPlayer.loadSound("drone_hit_2", "resources/sound_drone_hit_2.wav");
	soundPlayer.loadSound("drone_hit_3", "resources/sound_drone_hit_3.wav");
	soundPlayer.loadSound("drone_hit_4", "resources/sound_drone_hit_4.wav");
	soundPlayer.loadSound("475", "resources/475.wav");
	soundPlayer.loadSound("menu_music", "resources/atmospheric_menu_bit_2.wav");
	snowSystem = SnowSystem(&spriteCollection, &screenW, &screenH, camera.getPosition());
	snowSystem2 = SnowSystem(&spriteCollection, &screenW, &screenH, camera.getPosition());
	camera.setScreenDimensions(&screenW, &screenH);
	camera.setScreenshakeCutoff(0.1);
	camera.setScreenshakeDecay(0.9);
	spriteCollection.setUseCamera(true);
	spriteCollection.setPCamera(&camera);
	spriteCollection.setOrderZ(true);
	spriteCollection.addFont("resources/fonts/Hacked_CRT.TTF");
	spriteCollection.addFont("resources/fonts/LLDOT2__.TTF");

	
	spriteCollection.setWindowDimensions(&screenW, &screenH);
	ambientLightColour = sf::Glsl::Vec3(255/255.0, 253/255.0, 240/255.0);
	//console.addCommand(commandPlaySound, "wind");
	int id = soundPlayer.playSoundByName("wind", 0.20);
	soundPlayer.loopSound(id);
	//blizzard conditions

	controlSwitcher.setControlling(false);

	music_id = soundPlayer.playSoundByName("menu_music", 0.6);
	soundPlayer.loopSound(music_id);
	loadMenu();
}

void Game::HandleInput() {
	console.addTime("Start of handleinput");
	inputManager.update();
	console.addTime("Start of handleinput1");
	if (!mainMenu) {
		if (inputManager.onKeyDown(space)) {
			//console.addCommand(commandPlaySound, "hh");
			//console.addCommand(commandShakeScreen, 15.0f);	
			controlSwitcher.switchControl();
		}
		if (inputManager.isKeyDown(f)) {
			console.addCommand(commandEnableDebug, 1);
			debugMode = true;
		}
		if (inputManager.isKeyDown(g)) {
			console.addCommand(commandEnableDebug, 0);
			debugMode = false;
		}
		if (inputManager.isKeyDown(r)) {
			/*if (snowOpacity <= 0.99) {
				snowOpacity += 0.01;
				snowSystem.setOpacity(snowOpacity);
			}*/
			controlSwitcher.drawOverlay();
		}
		if (inputManager.onKeyDown(t)) {
			console.addCommand(commandAddObject, objectEnemy, inputManager.translatedMouseX, inputManager.translatedMouseY);
			//if (snowOpacity >= 0.01) {
			//	snowOpacity -= 0.01;
			//	snowSystem.setOpacity(snowOpacity);
			//}
		}
		if (inputManager.isKeyDown(y)) {
			//snowSystem.setSpeed(10);
			//snowSystem.setFallAngle(0.5);
			//snowSystem.setSize(50);
		}
		if (inputManager.isKeyDown(u)) {


			//snowSystem.setSpeed(1);
			//snowSystem.setFallAngle(1.6);
			//snowSystem.setSize(30);
		}
		if (inputManager.onKeyDown(escape)) {
			mainMenu = true;
			spriteCollection.setPipelineIndex(0);
			unloadGameplay();
			loadMenu();
		}
	}
	else {
		if (inputManager.onKeyDown(space)) {
			mainMenu = false;
			spriteCollection.setPipelineIndex(1);
			unloadMenu();
			loadGameplay();

		}
	}

	spriteCollection.setFrame(frame);
}

void Game::Run() {
	console.addTime("Start of run");

	if (!mainMenu) {
		//in game
		if (controlSwitcher.getControlling()) {
			console.setControlPosition(controlSwitcher.getControlPosition());
		}
		objectCollection.update();
		if (objectCollection.getControlledDead()) {
			controlSwitcher.setControlling(false);
		}
		objectCollection.runCollisionDetection();
		while (console.getSize() > 0) {
			commandExecuter.execute(console.getCommand());
		}

		snowSystem.run(camera.getPosition());
	}
	else {
		//menu
		snowSystem.run(camera.getPosition());
		snowSystem2.run(camera.getPosition());
	}
	soundPlayer.update();
	inputManager.translateMouseCoords(camera.getPosition().x - screenW / 2, camera.getPosition().y - screenH / 2);
	console.incrementFrame();
}

void Game::Draw() {
	console.addTime("Start of draw");
	
	pWindow->clear();

	if (!mainMenu) {
		spriteCollection.setPipelineIndex(0);
		//in game
		camera.runscreenShake();
		spriteCollection.addImageDraw(spriteCollection.getPointerFromName("white_background"), camera.getPosition().x - screenW / 2 - 100, camera.getPosition().y - screenH / 2 - 1000, -100000, 1, 1);
		objectCollection.draw();
		snowSystem.draw(100000);
		//objectCollection.drawHealthBars();
		spriteCollection.setPipelineIndex(1);
		
	}
	else {
		spriteCollection.setPipelineIndex(0);
		//menu 3000x1638
		float scale;
		if (3000.0f / 1638.0f > (float)screenW / (float)screenH) {
			// means taller, so need to fit height
			scale = (float)screenH / 1638.0f;
		}
		else {
			//need to fit height
			scale = (float)screenW / 3000.0f;
			
		}
		spriteCollection.addImageDraw(spriteCollection.getPointerFromName("menu_bg"), camera.getPosition().x - screenW / 2, camera.getPosition().y - screenH / 2, -100, scale, 1);
		spriteCollection.addImageDraw(spriteCollection.getPointerFromName("menu_mc"), camera.getPosition().x - screenW / 2, camera.getPosition().y + screenH / 2 - 5*162, 1, 5, 1);
		if (frame % 350 < 340) {
			spriteCollection.addImageDraw(spriteCollection.getPointerFromName("menu_eyes"), camera.getPosition().x - screenW / 2 - 10, camera.getPosition().y + screenH / 2 - 5  * 162, 2, 5, 1);
		}
		snowSystem.drawMenu(-50, 1);
		snowSystem2.drawMenu(10, 2);
	}
	spriteCollection.drawAll();
	frame++;

	//debug timing stuff
	console.addTime("End of draw");
	if (console.hasTimeStamps()) {
		TimeStamp ts1 = console.getTimeStamp();
		if (console.hasTimeStamps()) {
			TimeStamp ts2 = console.getTimeStamp();
			int offset = 0;
			if (debugMode) {
				spriteCollection.addAbsoluteTextDraw(1, 10, 100 + offset, 10000000, ts1.label + ": " + std::to_string(ts2.time - ts1.time), 30, sf::Color::White);
			}
			while (console.hasTimeStamps()) {
				ts1 = ts2;
				ts2 = console.getTimeStamp();
				offset += 40;
				if (debugMode) {
					spriteCollection.addAbsoluteTextDraw(1, 10, 100 + offset, 10000000, ts1.label + ": " + std::to_string(ts2.time - ts1.time), 30, sf::Color::White);
				}
			}
		}
	}
	console.addTime("Pre draw");
	
	
}

void Game::finishAudio(){
	soundPlayer.finish();
}

void Game::loadGameplay(){
	snowSystem.setSpeed(5);
	snowSystem.setFallAngle(0.5);
	snowSystem.setSize(80);
	snowOpacity = 0.4;
	snowSystem.setOpacity(snowOpacity);
	snowSystem.setSinMultiplier(1);

	objectCollection.setDebug(false);
	objectCollection.addMainCharacter(0, 0);
	objectCollection.addRover(-100, -100);
	objectCollection.addRelay(-150, 00);
	objectCollection.addMarketRelay(150, 0);
	objectCollection.addAutoTurret(0, -150);
	for (int i = 0; i < 100; i++) {
		objectCollection.addScapMetalPile(-3000 + (rand() % 6000), -3000 + (rand() % 6000));
	}
	glm::vec2 temp;
	for (int i = 0; i < 40; i++) {
		temp = glm::vec2(-3000 + (rand() % 6000), -3000 + (rand() % 6000));
		if (sqrt(temp.x * temp.x + temp.y * temp.y) > 800) {
			objectCollection.addEnemy(temp.x, temp.y);
		}
		else {
			i--;
		}
	}
	console.addCommand(commandSetCameraFocusId, 0);
	console.addCommand(commandEnableObjectControls, 0);
	controlSwitcher.setCurrentControlled(0);

	soundPlayer.stopSound(music_id);
	soundPlayer.update();
	music_id = soundPlayer.playSoundByName("475", 0.6);
	soundPlayer.loopSound(music_id);
}

void Game::unloadGameplay(){
	objectCollection.clear();
	controlSwitcher.setControlling(false);
}

void Game::loadMenu(){
	snowSystem.setSpeed(3);
	snowSystem.setFallAngle(1.5);
	snowSystem.setSize(90);
	snowSystem.setOpacity(0.3);
	snowSystem.setSinMultiplier(2);
	snowSystem2.setSpeed(3);
	snowSystem2.setFallAngle(1.5);
	snowSystem2.setSize(25);
	snowSystem2.setOpacity(0.2);
	snowSystem2.setSinMultiplier(2);

	soundPlayer.stopSound(music_id);
	soundPlayer.update();
	music_id = soundPlayer.playSoundByName("menu_music", 0.6);
	soundPlayer.loopSound(music_id);
}

void Game::unloadMenu() {

}
