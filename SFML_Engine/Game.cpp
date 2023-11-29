#include "Game.h"
#include <windows.h>
#include <iostream>
#include <ctime>
#include "CollisionDetection.h"

Game::Game(sf::RenderWindow* pwindow)  {
	screenW = pwindow->getSize().x;
	screenH = pwindow->getSize().y;
	pWindow = pwindow;
	graphics = Graphics(pwindow);
	camera = Camera();
	inputManager = InputManager(pwindow, &screenW, &screenH);

	auto defaultPipeline = std::make_shared<RenderingPipeline>(false);
	auto pipelineL = std::make_shared<RenderingPipeline>(false);
	auto pipelineN = std::make_shared<RenderingPipeline>(false);

	shaderManager = ShaderManager();

	
	DWORD bufferSize = MAX_PATH;
	std::vector<wchar_t> currentPath(bufferSize);

	bufferSize = GetCurrentDirectory(bufferSize, currentPath.data());

	if (bufferSize > 0 && bufferSize < currentPath.size()) {
		std::wcout << L"Current directory: " << currentPath.data() << std::endl;
	}
	else {
		std::wcerr << L"Error getting current directory." << std::endl;
	}


	// Loading shaders with ShaderManager
	shaderManager.loadShader("brightness_threshold", "shaders/brightness_threshold.frag", sf::Shader::Fragment);
	shaderManager.loadShader("lighting", "shaders/lighting.frag", sf::Shader::Fragment);
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
	pipelineN->addStage(shaderManager.getShader("bloom"));
	//pipelineN->addStage(shaderManager.getShader("bloom"));
	//pipelineN->addStage(shaderManager.getShader("bloom_v"));
	//pipelineN->addStage(shaderManager.getShader("bloom"));
	//pipelineN->addStage(shaderManager.getShader("bloom_v"));
	
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
	multiPipelineManager.addBlendShader(shaderManager.getShader("blend"));
	

	spriteCollection = SpriteCollection(pWindow, &graphics, &multiPipelineManager);

	spriteCollection.setPipelineIndex(0);

	spriteCollection.setLightShader(shaderManager.getShader("lighting"));

	soundPlayer.setGlobalVolume(1);
	console = Console();
	timer = Timer(250, &console);
	inventory = Inventory();
	objectCollection = ObjectCollection(&console, &inputManager, &spriteCollection, &soundPlayer, &camera, &inventory);
	controlSwitcher = ControlSwitcher(&objectCollection, &console, &spriteCollection);
	builder = Builder(&spriteCollection, &inventory, &console, &inputManager);
	uiManager = UIManager(&console, &spriteCollection, &inputManager, &builder);
	commandExecuter = CommandExecuter(&objectCollection, &soundPlayer, &camera, &spriteCollection, &inputManager, &uiManager);

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
	spriteCollection.loadTexture("jammer_stack_1", "resources/jammer_stack_1.png");
	spriteCollection.loadTexture("market_relay", "resources/market_relay.png");
	spriteCollection.loadTexture("market_relay_stack_1", "resources/market_relay_stack_1.png");
	spriteCollection.loadTexture("autoturret_base_stack", "resources/autoturret_base_stack.png");
	spriteCollection.loadTexture("autoturret_barrel_stack", "resources/autoturret_barrel_stack.png");
	spriteCollection.loadTexture("DefenseOrb_stack", "resources/DefenseOrbStack.png");
	spriteCollection.loadTexture("white_rect", "resources/white_rect.png");
	spriteCollection.loadTexture("menu_bg", "resources/menu_bg.png");
	spriteCollection.loadTexture("menu_mc", "resources/menu_mc_p.png");
	spriteCollection.loadTexture("menu_eyes", "resources/menu_eyes_p.png");
	spriteCollection.loadTexture("menu_snow", "resources/menu_snow.png");
	spriteCollection.loadTexture("decoration_smoke_1", "resources/smoke_12.png");
	spriteCollection.loadTexture("decoration_smoke_2", "resources/smoke_22.png");
	spriteCollection.loadTexture("decoration_smoke_3", "resources/smoke_32.png");
	spriteCollection.loadTexture("decoration_smoke_4", "resources/smoke_42.png");
	spriteCollection.loadTexture("decoration_footprint_1", "resources/decoration_footprint_1.png");
	sprite1 = spriteCollection.getPointerFromName("pic1");
	sprite2 = spriteCollection.getPointerFromName("pic2");
	sprite3 = spriteCollection.getPointerFromName("pic3");
	//spriteSheet1 = SpriteSheet(pwindow, &spriteCollection, "animation1", 144, 172, 4, 1);
	//spriteSheet1 = SpriteSheet(pwindow, &spriteCollection, "animation2", 16, 26, 6, 2);
	//spriteSheet1.setDoesReset(false);
	
	glm::vec2 _p1 = glm::vec2(819.454712,-128.555573);
	glm::vec2 _p2 = glm::vec2(1366.09082, -680.026733);
	BoundingBox _boundingBox;
	_boundingBox.x = 899.000000;
	_boundingBox.y = -247.000000;
	_boundingBox.w = 32.0000000;
	_boundingBox.h = 32;
	glm::vec2 left = CollisionDetection::getLineIntersect(_p1, _p2, glm::vec2(_boundingBox.x, _boundingBox.y), glm::vec2(_boundingBox.x, _boundingBox.y + _boundingBox.h));
	glm::vec2 bottom = CollisionDetection::getLineIntersect(_p1, _p2, glm::vec2(_boundingBox.x, _boundingBox.y), glm::vec2(_boundingBox.x + _boundingBox.w, _boundingBox.y));
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
	soundPlayer.loadSound("rover_move_1", "resources/sound_rover_move_2.wav");
	soundPlayer.loadSound("rover_mine_1", "resources/sound_rover_mine_1.wav");
	soundPlayer.loadSound("pickup", "resources/sound_pickup.wav");
	soundPlayer.loadSound("drop", "resources/sound_drop.wav");
	soundPlayer.loadSound("mine_hit_1", "resources/sound_mine_hit_2.wav");
	soundPlayer.loadSound("transfer", "resources/sound_transfer.wav");
	soundPlayer.loadSound("laser_shot", "resources/sound_laser_shot.wav");
	soundPlayer.loadSound("laser_shot2", "resources/sound_laser_shot2.wav");
	soundPlayer.loadSound("laser_impact", "resources/sound_laser_impact.wav");
	soundPlayer.loadSound("drone_death_2", "resources/sound_drone_death_2.wav");
	soundPlayer.loadSound("drone_zap_1", "resources/sound_drone_zap_1.wav");
	soundPlayer.loadSound("drone_zap_2", "resources/sound_drone_zap_2.wav");
	soundPlayer.loadSound("drone_zap_3", "resources/sound_drone_zap_3.wav");
	soundPlayer.loadSound("drone_zap_4", "resources/sound_drone_zap_4.wav");
	soundPlayer.loadSound("drone_zap_5", "resources/sound_drone_zap_5.wav");
	soundPlayer.loadSound("relay_ambient_2", "resources/sound_market_relay_ambient_1.wav"); 
	soundPlayer.loadSound("drone_ambient_1", "resources/sound_drone_ambient_2.wav");
	soundPlayer.loadSound("relay_ambient_3", "resources/sound_relay_ambient_4.wav");
	soundPlayer.loadSound("drone_hit_1", "resources/sound_drone_hit_1.wav");
	soundPlayer.loadSound("drone_hit_2", "resources/sound_drone_hit_2.wav");
	soundPlayer.loadSound("drone_hit_3", "resources/sound_drone_hit_3.wav");
	soundPlayer.loadSound("drone_hit_4", "resources/sound_drone_hit_4.wav");
	soundPlayer.loadSound("explosion", "resources/sound_explosion.wav");
	soundPlayer.loadSound("explosion1", "resources/sound_explosion1.wav");
	soundPlayer.loadSound("explosion2", "resources/sound_explosion2.wav");
	soundPlayer.loadSound("explosion3", "resources/sound_explosion3.wav");
	soundPlayer.loadSound("explosion4", "resources/sound_explosion4.wav");
	soundPlayer.loadSound("beam_1", "resources/sound_beam_3.wav");
	soundPlayer.loadSound("jammer_ambient_1", "resources/sound_jammer_ambient_1.wav");
	soundPlayer.loadSound("475", "resources/475.wav");
	soundPlayer.loadSound("menu_music", "resources/atmospheric_menu_bit_2.wav");
	soundPlayer.loadSound("menu_hover", "resources/sound_menu_hover.wav");
	soundPlayer.loadSound("menu_click", "resources/sound_menu_click.wav");
	snowSystem = SnowSystem(&spriteCollection, &camera, &screenW, &screenH, camera.getPosition());
	snowSystem2 = SnowSystem(&spriteCollection, &camera, &screenW, &screenH, camera.getPosition());
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
	int id = soundPlayer.playSoundByName("wind", 0.15);
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
		if (inputManager.onKeyDown(r)) {
			//console.addCommand(commandAddObject, objectJammer, inputManager.translatedMouseX, inputManager.translatedMouseY);
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
		if (inputManager.onKeyDown(u)) {

			//console.addCommand(commandAddObject, objectScrapMetalDrop, inputManager.translatedMouseX, inputManager.translatedMouseY);
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
		if (inputManager.onKeyDown(z)) {
			uiManager.loadNewMenu(MenuType::builder);
			uiManager.setActive(true);
			inputManager.setMenuMode(true);
		}
		if (inputManager.onKeyDown(x)) {
			uiManager.setActive(false);
			inputManager.setMenuMode(false);
		}
		if (controlSwitcher.getControlling()) {
			console.setControlPosition(controlSwitcher.getControlPosition());
		}
		objectCollection.update();
		builder.update();
		if (objectCollection.getControlledDead()) {
			controlSwitcher.setControlling(false);
		}
		objectCollection.runCollisionDetection();
		while (console.getSize() > 0) {
			commandExecuter.execute(console.getCommand());
		}
		if (inputManager.isKeyDown(c)) {
			snowSystem.changeSize(-1);
		}
		if (inputManager.isKeyDown(v)) {
			snowSystem.changeSize(+1);
		}
		snowSystem.run();
	}
	else {
		//menu

		snowSystem.run();// glm::vec2(screenW / 2, screenH / 2));
		snowSystem2.run();//glm::vec2(screenW/2, screenH/2));
	}
	soundPlayer.update();
	inputManager.translateMouseCoords(camera.getPosition().x - screenW / 2, camera.getPosition().y - screenH / 2);
	uiManager.update();
	console.incrementFrame();

}

void Game::Draw() {
	console.addTime("Start of draw");
	
	pWindow->clear();

	if (!mainMenu) {
		spriteCollection.setPipelineIndex(0);
		//in game
		camera.runscreenShake();
		spriteCollection.addImageDraw(spriteCollection.getPointerFromName("white_background"), camera.getPosition().x - screenW / 2 - 1000, camera.getPosition().y - screenH / 2 - 1000, -100000, 1, 1, 4500, 4500);
		//spriteCollection.drawLightSource(glm::vec2(0,0), glm::vec3(255, 255, 255), 0.3, 0);
		objectCollection.draw();
		snowSystem.draw(100000);
		//objectCollection.drawHealthBars();
		//spriteCollection.setFullBrightMode(true);
		//spriteCollection.addTextDraw(1, 0, 0, 100, "TEST_TEST_TEST_TEST", 100, sf::Color(60, 255, 100, 255));
		//spriteCollection.addRectDraw(0, 0, 300, 300, 300, sf::Color(60, 255, 100, 255));
		//spriteCollection.setFullBrightMode(false);
		uiManager.draw();
		builder.draw();
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
		spriteCollection.setAbsoluteMode(true);
		spriteCollection.addImageDraw(spriteCollection.getPointerFromName("menu_bg"), 0, 0, -100, scale, 1, scale*3000, scale*1638);
		spriteCollection.addImageDraw(spriteCollection.getPointerFromName("menu_mc"), 0, screenH - 5*162, 1, 5, 1, 5*139, 5*162);
		if (frame % 350 < 340) {
			spriteCollection.addImageDraw(spriteCollection.getPointerFromName("menu_eyes"), 0 - 10, screenH - 5  * 162, 2, 5, 1, 5*141, 5*165);
		}
		snowSystem.drawMenu(-50, 1);
		snowSystem2.drawMenu(10, 2);
		uiManager.draw();
		spriteCollection.setAbsoluteMode(false);
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
				spriteCollection.setAbsoluteMode(true);
				spriteCollection.addTextDraw(1, 10, 100 + offset, 10000000, ts1.label + ": " + std::to_string(ts2.time - ts1.time), 30, sf::Color::White);
				spriteCollection.setAbsoluteMode(false);
			}
			while (console.hasTimeStamps()) {
				ts1 = ts2;
				ts2 = console.getTimeStamp();
				offset += 40;
				if (debugMode) {
					spriteCollection.setAbsoluteMode(true);
					spriteCollection.addTextDraw(1, 10, 100 + offset, 10000000, ts1.label + ": " + std::to_string(ts2.time - ts1.time), 30, sf::Color::White);
					spriteCollection.setAbsoluteMode(false);
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
	snowSystem.setSpeed(4.5);
	snowSystem.setFallAngle(0.5);
	snowSystem.setSize(50);
	snowOpacity = 0.6;
	snowSystem.setOpacity(snowOpacity);
	snowSystem.setSinMultiplier(2);

	objectCollection.setDebug(false);
	objectCollection.addMainCharacter(0, 0);
	objectCollection.addRover(-100, -100);
	objectCollection.addRelay(-150, 00);
	objectCollection.addMarketRelay(150, 0);
	objectCollection.addAutoTurret(0, -150);

	

	glm::vec2 temp;
	int genRange = 4000;
	for (int i = 0; i < 320; i++) {
		objectCollection.addScapMetalPile(-genRange + (rand() % (genRange * 2)), -genRange + (rand() % (genRange * 2)));
	}
	for (int i = 0; i < 120; i++) {
		temp = glm::vec2(-genRange + (rand() % (genRange*2)), -genRange + (rand() % (genRange * 2)));
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
	objectCollection.setControlledDead(false);

	soundPlayer.stopSound(music_id);
	soundPlayer.update();
	music_id = soundPlayer.playSoundByName("475", 0.5);
	soundPlayer.loopSound(music_id);
}

void Game::unloadGameplay(){
	objectCollection.clear();
	controlSwitcher.setControlling(false);
}

void Game::loadMenu(){
	snowSystem.setSpeed(3);
	snowSystem.setFallAngle(1.5);
	snowSystem.setSize(100 * (float)screenH/1080.0f);
	snowSystem.setOpacity(0.3);
	snowSystem.setSinMultiplier(2);
	snowSystem2.setSpeed(3);
	snowSystem2.setFallAngle(1.5);
	snowSystem2.setSize(25 * (float)screenH / 1080.0f);
	snowSystem2.setOpacity(0.2);
	snowSystem2.setSinMultiplier(2);

	soundPlayer.stopSound(music_id);
	soundPlayer.update();
	music_id = soundPlayer.playSoundByName("menu_music", 0.6);
	soundPlayer.loopSound(music_id);
	camera.setPosition(screenW / 2, screenH / 2);
}

void Game::unloadMenu() {

}
