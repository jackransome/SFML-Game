#pragma once
#include "Graphics.h"
#include "CommandExecuter.h"
#include "Console.h"
#include "Timer.h"
#include "SnowSystem.h"
#include "ControlSwitcher.h"
#include "ShaderManager.h"
#include "UIManager.h"
#include "MusicSystem.h"
#include "Coordinator.h"
#include "PowerManager.h"

class Game {
public:
	Game(sf::RenderWindow* pwindow);
	void HandleInput();
	void Run();
	void Draw();
	void finishAudio();
	void loadGameplay();
	void unloadGameplay();
	void loadMenu();
	void unloadMenu();
	void loadEndScreen();
	void unloadEndScreen();
private:
	bool debugMode = false;
	int screenW;
	int screenH;
	bool lastSpace = false;
	TextureWrapper *sprite1;
	TextureWrapper* sprite2;
	TextureWrapper* sprite3;
	TextureWrapper* animation1;
	unsigned long frame = 0;
	glm::vec2 tranformedMousePos;
	sf::RenderWindow* pWindow;
	Graphics graphics;
	InputManager inputManager;
	SpriteCollection spriteCollection;
	SoundPlayer soundPlayer;
	Camera camera;
	SpriteSheet spriteSheet1;
	SpriteSheet spriteSheet2;
	SpriteSheet spriteSheet3;
	SpriteSheet spriteSheet4;
	SpriteSheet spriteSheet5;
	SpriteSheet spriteSheet6;
	SpriteSheet spriteSheet7;
	ObjectCollection objectCollection;
	ControlSwitcher controlSwitcher;
	Console console;
	CommandExecuter commandExecuter;
	Timer timer;
	SnowSystem snowSystem;
	SnowSystem snowSystem2;
	Builder builder;
	Inventory inventory;
	UIManager uiManager;
	sf::Shader shader1;
	float ambientLightLevel = 0;
	sf::Glsl::Vec3 ambientLightColour;
	float snowOpacity = 0.5;
	float shaderNoiseIntensity = 1;
	float daylightPhase = 0;
	sf::Shader* shaders[10];
	MultiPipelineManager multiPipelineManager;
	ShaderManager shaderManager;
	MusicSystem musicSystem;
	Coordinator coordinator;
	PowerManager powerManager;
	int gameState = 0;
	bool gameLive = false;
	float zoomLevel = 1;
	float zoomTarget = 1;
};