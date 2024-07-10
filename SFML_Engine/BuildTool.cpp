#include "BuildTool.h"

BuildTool::BuildTool(Console* _pConsole, SpriteCollection* _pSpriteCollection) :
	Tool(3, ItemType::buildTool, _pConsole, _pSpriteCollection, "buildToolIcon") {
	
}

BuildTool::~BuildTool() { }

void BuildTool::activate(glm::vec2 position, glm::vec2 target) {

}

void BuildTool::drawUsing(glm::vec2 position, glm::vec2 target) {

}
