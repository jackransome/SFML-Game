#pragma once
#include <glm/glm.hpp>

class Camera {
public:
	Camera();
	void setPosition(glm::vec2 newPosition);
	void setScreenDimensions(int w, int h);
	glm::vec2 getPosition();
	glm::vec2 transformPosition(glm::vec2 toTransform);
private:
	int screenW;
	int screenH;
	glm::vec2 position;
};