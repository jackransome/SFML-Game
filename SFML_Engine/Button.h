#pragma once
#include "SpriteCollection.h"
#include "Console.h"
#include "Builder.h"

enum class ButtonType {
	build, back, openMenu
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