#pragma once
#include "Graphics.h"
#include "CommandExecuter.h"
#include "Console.h"
#include "Timer.h"
#include "SnowSystem.h"


class Game {
public:
	Game(sf::RenderWindow* pwindow);
	void HandleInput();
	void Run();
	void Draw();
	void finishAudio();
private:
	int screenW;
	int screenH;
	bool lastSpace = false;
	Image *sprite1;
	Image* sprite2;
	Image* sprite3;
	Image* animation1;
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
	Console console;
	CommandExecuter commandExecuter;
	Timer timer;
	SnowSystem snowSystem;
	sf::Shader shader1;
	float ambientLightLevel = 0;
	sf::Glsl::Vec3 ambientLightColour;
	float snowOpacity = 0.5;
	float shaderNoiseIntensity = 1;
	float daylightPhase = 0;
	sf::Shader* shaders[10];
};