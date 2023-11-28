#pragma once
#include "SpriteCollection.h"
#include "Console.h"
#include "Builder.h"

enum class ButtonType {
	build, back, openMenu
};

class Button {
public:
	Button(SpriteCollection* _pSpriteCollection, ButtonType _type, glm::vec4 _bbox);
	virtual void press() {};
	virtual void draw() {};
private:
	
	glm::vec4 bbox;
	ButtonType type;
	SpriteCollection* pSpriteCollection;

protected:
	bool active;
	void drawBox();
};

class BuildButton : Button {
public:
	BuildButton(SpriteCollection* _pSpriteCollection, BuildType _buildType, glm::vec4 _bbox);
	virtual void press() override;
	virtual void draw() override;
private:
	
	BuildType buildType;
};