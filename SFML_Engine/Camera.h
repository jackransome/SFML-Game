#pragma once
#include <glm/glm.hpp>

class Camera {
public:
	Camera();
	void setPosition(glm::vec2 newPosition);
	void setPosition(float x, float y);
	void setScreenDimensions(int w, int h);
	glm::vec2 getPosition();
	glm::vec2 transformPosition(glm::vec2 toTransform);
	void setScreenshakeAmount(int amount);
	void addScreenshake(int amount);
	void setScreenshakeDecay(float decay);
	void setScreenshakeCutoff(float cutoff);
	void runscreenShake();
private:
	float screenshake = 0;
	float screenshakeDecay;
	float screenshakeCutoff;
	int screenW;
	int screenH;
	glm::vec2 position;
	glm::vec2 screenshakePosition;
};