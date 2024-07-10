#pragma once
#include "Tool.h"

class BuildTool : public Tool {
public:
	BuildTool(Console* _pConsole, SpriteCollection* _pSpriteCollection);
	~BuildTool();
	void activate(glm::vec2 position, glm::vec2 target);
	void drawUsing(glm::vec2 position, glm::vec2 target);
private:
	float charge = 0;
};