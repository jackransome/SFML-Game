#pragma once
#include "SpriteCollection.h"
#include "Console.h"
#include "Builder.h"
#include "SpriteSheet.h"

enum class ButtonType {
	build, back, openMenu, startGame, goToMain
};

class Button {
public:
	Button(Console* _pConsole, SpriteCollection* _pSpriteCollection, ButtonType _type, glm::vec4 _bbox);
	virtual void press() {};
	virtual void draw() {};
	virtual void update() {};
	bool getActive();
	void setHover(bool hover);
	bool getHover();
	glm::vec4 getBbox();

protected:
	Console* pConsole;
	glm::vec4 bbox;
	ButtonType type;
	SpriteCollection* pSpriteCollection;
	bool hoverOver = false;
	bool active;
	void drawBox();
	SpriteSheet imgGrey;
	SpriteSheet imgReady;
	SpriteSheet imgHover;
};

class BuildButton : public Button {
public:
	BuildButton(Console* _pConsole, SpriteCollection* _pSpriteCollection, Builder* _pBuilder, BuildType _buildType, glm::vec4 _bbox);
	virtual void press() override;
	virtual void draw() override;
	virtual void update() override;
private:
	Builder* pBuilder;
	BuildType buildType;

};

class StartGameButton : public Button {
public:
	StartGameButton(Console* _pConsole, SpriteCollection* _pSpriteCollection, glm::vec4 _bbox);
	virtual void press() override;
	virtual void draw() override;
};

class MainMenuButton : public Button {
public:
	MainMenuButton(Console* _pConsole, SpriteCollection* _pSpriteCollection, glm::vec4 _bbox);
	virtual void press() override;
	virtual void draw() override;
};